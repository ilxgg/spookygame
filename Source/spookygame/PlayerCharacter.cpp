// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

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

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::ManageStress(float DeltaTime)
{

}

void APlayerCharacter::ManageStamina(float DeltaTime)
{
	if (CurrentState = EPlayerStates::Running)
	{
		//drains stamina
	}
	else
	{
		//regen stamina
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);

}

void APlayerCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void APlayerCharacter::MoveRight(float value)
{
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

void APlayerCharacter::IncreaseStress(int amount)
{
	StressComponent->IncreaseStress(amount);
}

void APlayerCharacter::DecreaseStress(int amount)
{
	StressComponent->DecreaseStress(amount);
}

EPlayerStates APlayerCharacter::GetPlayerState()
{
	return CurrentState;
}

