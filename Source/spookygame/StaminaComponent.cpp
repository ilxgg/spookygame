// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	StaminaMax = 100;
	StaminaCurrent = 0;

	RunningSpeed = 500;
	WalkSpeed = 260;

	bCanRun = false;
	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	
	StaminaCurrent = StaminaMax;
	CheckStamina();
	// ...
	
}




// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UStaminaComponent::getCurrentStamina()
{
	return (StaminaCurrent/StaminaMax);
}

void UStaminaComponent::ManageStamina(float DeltaTime, bool IsRunning)
{
	if (IsRunning)
	{
		StaminaCurrent -= (RunningStaminaDrain * DeltaTime);
		CheckStamina();
	}
	else
	{
		StaminaCurrent += (StaminaRegen * DeltaTime);
		CheckStamina();
	}
}

bool UStaminaComponent::canSprint()
{
	CheckStamina();
	return bCanRun;
}

float UStaminaComponent::getMovementSpeed(bool IsRunning)
{
	if (IsRunning)
	{
		return RunningSpeed;
	}
	else
	{
		return WalkSpeed;
	}
}

void UStaminaComponent::CheckStamina()
{
	if (StaminaCurrent > StaminaMax)
	{
		StaminaCurrent = StaminaMax;
		bCanRun = true;
	}
	if (StaminaCurrent <= 0)
	{
		StaminaCurrent = 0;
		bCanRun = false;
	}
	if (StaminaCurrent > 0)
	{
		bCanRun = true;
	}
}
