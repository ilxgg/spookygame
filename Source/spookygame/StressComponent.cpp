// Fill out your copyright notice in the Description page of Project Settings.


#include "StressComponent.h"

// Sets default values for this component's properties
UStressComponent::UStressComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	StressCurrent = 0;
	StressMax = 100;
	// ...
}


// Called when the game starts
void UStressComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UStressComponent::IncreaseStress(float value)
{
	StressCurrent += value;
	CheckStressLevel();
	OnStressUpdate(GetCurrentStress());
}

void UStressComponent::DecreaseStress(float value)
{
	StressCurrent -= value;
	CheckStressLevel();
	OnStressUpdate(GetCurrentStress());
}

float UStressComponent::GetCurrentStress()
{
	return (StressCurrent/float(StressMax));
}


// Called every frame
void UStressComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStressComponent::CheckStressLevel()
{
	if (StressCurrent > StressMax)
	{
		StressCurrent = StressMax;
		OnMaxStress();
	}
	if (StressCurrent < 0)
	{
		StressCurrent = 0;
	}
}

