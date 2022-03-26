// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractable.h"

ADoorInteractable::ADoorInteractable() 
{
	InteractionType = EInteractableType::Movable;
}

EInteractableType ADoorInteractable::Interact(AActor* InteractingActor)
{
	Open();
	return InteractionType;
}