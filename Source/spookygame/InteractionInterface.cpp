// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionInterface.h"

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.

EInteractableType IInteractionInterface::Interact(AActor* InteractingActor)
{
	return EInteractableType::None;
}

