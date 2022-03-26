// Fill out your copyright notice in the Description page of Project Settings.


#include "HidableBase.h"

AHidableBase::AHidableBase()
{
	HideLocation = CreateDefaultSubobject<USceneComponent>("HideLocation");
	HideLocation->SetupAttachment(RootComponent);

	ExitLocation = CreateDefaultSubobject<USceneComponent>("ExitLocation");
	ExitLocation->SetupAttachment(RootComponent);
	
	bIsHidingActor = false;

	InteractionType = EInteractableType::Hidable;
}

EInteractableType AHidableBase::Interact(AActor* InteractingActor)
{
	if (!bIsHidingActor)
	{
		Hide(InteractingActor);
		bIsHidingActor = true;
		UE_LOG(LogTemp, Warning, TEXT("Hiding Actor"));
	}
	else
	{
		EndHide(InteractingActor);
		bIsHidingActor = false;
		UE_LOG(LogTemp, Warning, TEXT("Not Hiding Actor"));
	}

	return InteractionType;
}

void AHidableBase::Hide(AActor* HidingActor)
{
	HidingActor->SetActorLocation(HideLocation->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);
}

void AHidableBase::EndHide(AActor* HidingActor)
{
	HidingActor->SetActorLocation(ExitLocation->GetComponentLocation());
}