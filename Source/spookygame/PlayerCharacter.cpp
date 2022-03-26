// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "InteractableBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	StressComponent = CreateDefaultSubobject<UStressComponent>("StressComp");

	CurrentState = EPlayerStates::Walking;
	SensMulti = 1.f;

	InteractRange = 130.f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::ManageStress(float DeltaTime)
{
	if (CurrentState != Hiding)
	{
		int ArrLength = StressPool.Num();
		for (int32 it = 0; it < ArrLength; it++)
		{
			if (StressPool[it].Lifetime >= StressPool[it].Duration)
			{
				StressPool.RemoveAt(it);
				break;
			}
			float perSecond = StressPool[it].NewStressVal / StressPool[it].Duration;
			StressPool[it].Lifetime += DeltaTime;
			IncreaseStress(perSecond * DeltaTime);
		}
	}
	else
	{
		if (bPlayerInitialHide)
		{
			StressPool.Empty();
			bPlayerInitialHide = false;
		}
		DecreaseStress(StressHidingDecrease * DeltaTime);

	}
}

void APlayerCharacter::ManageStamina(float DeltaTime, bool IsRunning)
{
	if (IsRunning)
	{
		//drains stamina
	}
	else
	{
		//regen stamina
	}
}

void APlayerCharacter::ManageMovement()
{
	switch (CurrentState)
	{
	default:
		break;

	case(Hiding):
		UE_LOG(LogTemp, Warning, TEXT("Hiding"));
		break;

	case(Walking):
		UE_LOG(LogTemp, Warning, TEXT("Walking"));
		break;

	case(Running):
		UE_LOG(LogTemp, Warning, TEXT("Running"));
		break;
	
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageStamina(DeltaTime, false);
	ManageStress(DeltaTime);
	ManageMovement();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAction(FName("Interact"), IE_Pressed, this, &APlayerCharacter::TryInteract);

}

void APlayerCharacter::MoveForward(float value) //Move forward and back function, doesnt allow movement when hiding
{
	if (CurrentState != Hiding)
		AddMovementInput(GetActorForwardVector(), value);
}

void APlayerCharacter::MoveRight(float value) //Move left and right function, doesnt allow movement when hiding
{
	if (CurrentState != Hiding)
		AddMovementInput(GetActorRightVector(), value);
}

void APlayerCharacter::LookUp(float value)
{
		AddControllerPitchInput(value * SensMulti);
}

void APlayerCharacter::LookRight(float value)
{
		AddControllerYawInput(value * SensMulti);
}



void APlayerCharacter::IncreaseStress(float amount)
{
	StressComponent->IncreaseStress(amount);
}

void APlayerCharacter::DecreaseStress(float amount)
{
	StressComponent->DecreaseStress(amount);
}

EPlayerStates APlayerCharacter::GetPlayerState()
{
	return CurrentState;
}

EInteractableType APlayerCharacter::Interact(AActor* InteractingActor)
{
	return EInteractableType::None;
}

void APlayerCharacter::TryInteract()
{

	FHitResult Result;
	FVector CameraLoc = Camera->GetComponentLocation();
	FVector CameraRotVec = Camera->GetComponentRotation().Vector();
	DrawDebugSphere(GetWorld(), Camera->GetComponentLocation() + (CameraRotVec * InteractRange), 5.f, 26, FColor::Red, false, 3.f);
#define InteractionCollision ECC_GameTraceChannel1
	if (GetWorld()->LineTraceSingleByChannel(Result, Camera->GetComponentLocation(), Camera->GetComponentLocation() + (CameraRotVec * InteractRange), ECollisionChannel::InteractionCollision))
	{
		if (Cast<IInteractionInterface>(Result.Actor))
		{
			AInteractableBase* InteractObj = Cast<AInteractableBase>(Result.Actor);
			if (InteractObj)
			{
				EInteractableType Interaction = InteractObj->Interact(this); //Interacts with objects the player is looking at, interact function returns the interaction type of the object the player interacted with

				
				if (Interaction == Hidable && CurrentState == Hiding) //if the player is hiding and interacts with a hideable object then the player isnt hiding
				{
					CurrentState = Walking;
					ApplyStress(50.f, 1.f);
				}
				else if (Interaction == Hidable) //if the player interacts with a hidable object then they are hiding
				{
					CurrentState = Hiding;
					bPlayerInitialHide = true;
				}
				
					
				
			}
		}
	}

}

void APlayerCharacter::ApplyStress(float amount, float duration)
{
	StressPool.Add(FStressStruct(amount, duration));
}

