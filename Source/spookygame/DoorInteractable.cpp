// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractable.h"

ADoorInteractable::ADoorInteractable() 
{
	InteractionType = EInteractableType::Movable;
}

void ADoorInteractable::Interact(AActor* InteractingActor)
{
	Open();
}