// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldableBase.h"

AHoldableBase::AHoldableBase()
{
	InteractionType = Pickup;
}

EInteractableType AHoldableBase::Interact(AActor* InteractingActor)
{

	OnPickup();
	return InteractionType;
}

void AHoldableBase::OnPickup()
{
	StaticMesh->SetVisibility(false);
	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
