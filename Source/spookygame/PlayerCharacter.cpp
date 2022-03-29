// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "InteractableBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	StressComponent = CreateDefaultSubobject<UStressComponent>("StressComp");

	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>("StaminaComp");

	CurrentState = EPlayerStates::Walking;
	SensMulti = 1.f;

	InteractRange = 130.f;

	SprintToggle = false;
	SprintToggleSecondRelease = true;
	bIsMovementEnabled = true;

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
		StaminaComponent->ManageStamina(DeltaTime, IsRunning);
	}
	else
	{
		StaminaComponent->ManageStamina(DeltaTime, IsRunning);
	}
}

void APlayerCharacter::ManageMovement(float DeltaTime)
{
	switch (CurrentState)
	{
	default:
		break;

	case(Hiding):
		ManageStamina(DeltaTime, false);
		break;

	case(Walking):
		ManageStamina(DeltaTime, false);
		break;

	case(Running):
		ManageStamina(DeltaTime, true);
		break;
	
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageStress(DeltaTime);
	bool SprintCheck = StaminaComponent->canSprint();
	if(!SprintCheck && CurrentState == Running)
		ChangeState(Walking);
	ManageMovement(DeltaTime);

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
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::TrySprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::EndSprint);

}

void APlayerCharacter::MoveForward(float value) //Move forward and back function, doesnt allow movement when hiding
{
	if (bIsMovementEnabled)
		AddMovementInput(GetActorForwardVector(), value);
}

void APlayerCharacter::MoveRight(float value) //Move left and right function, doesnt allow movement when hiding
{
	if (bIsMovementEnabled)
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

void APlayerCharacter::TrySprint()
{
	if (StaminaComponent->canSprint() && CurrentState != Hiding)
	{
		ChangeState(Running);
	}
}

void APlayerCharacter::EndSprint()
{
	if (CurrentState != Hiding)
	{
		if(SprintToggle)
		{
			SprintToggleSecondRelease = !SprintToggleSecondRelease; 
			if (SprintToggleSecondRelease)
			{
				ChangeState(Walking);
			}
		}
		else
		{
			ChangeState(Walking);
		}
	}
}



void APlayerCharacter::IncreaseStress(float amount)
{
	StressComponent->IncreaseStress(amount);
}

void APlayerCharacter::DecreaseStress(float amount)
{
	StressComponent->DecreaseStress(amount);
}

void APlayerCharacter::DisableMovement()
{
	bIsMovementEnabled = false;
}

void APlayerCharacter::EnableMovement()
{
	bIsMovementEnabled = true;
}

void APlayerCharacter::ChangeState(EPlayerStates newState)
{
	switch (newState)
	{
	case Walking:
		if (CurrentState != newState)
		{
			EnableMovement();
			GetCharacterMovement()->MaxWalkSpeed = StaminaComponent->getMovementSpeed(false);
		}
		break;

	case Running:
		if (CurrentState != newState)
		{
			EnableMovement();
			GetCharacterMovement()->MaxWalkSpeed = StaminaComponent->getMovementSpeed(true);
		}
		break;

	case Hiding:
		if (CurrentState != newState)
		{
			DisableMovement();
			bPlayerInitialHide = true;
		}
		break;

	default:
		break;
	}
	CurrentState = newState;
	
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
					ChangeState(Walking);
				}
				else if (Interaction == Hidable) //if the player interacts with a hidable object then they are hiding
				{
					ChangeState(Hiding);
				}
				
					
				
			}
		}
	}

}

void APlayerCharacter::ApplyStress(float amount, float duration)
{
	StressPool.Add(FStressStruct(amount, duration));
}

