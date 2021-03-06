// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UENUM()
enum EInteractableType
{
	None, //Used as default value, does nothing if returned
	Hidable, //used for objects that you can hide in
	Objective, //todo
	Movable, //used for objects that move ie doors
	Pickup, //used for objects that player can pickup
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPOOKYGAME_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual EInteractableType Interact(AActor* InteractingActor); //function used when two actors interact




};
