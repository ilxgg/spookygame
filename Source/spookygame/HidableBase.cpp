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

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

EInteractableType AHidableBase::Interact(AActor* InteractingActor)
{
	if (!bIsHidingActor)
	{
		Hide(InteractingActor);
		bIsHidingActor = true;
	}
	else
	{
		EndHide(InteractingActor);
		bIsHidingActor = false;
	}

	return InteractionType;
}

void AHidableBase::Hide(AActor* HidingActor)
{
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HidingActor->SetActorLocation(HideLocation->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);
}

void AHidableBase::EndHide(AActor* HidingActor)
{
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HidingActor->SetActorLocation(ExitLocation->GetComponentLocation());
}