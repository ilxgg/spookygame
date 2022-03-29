// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "HoldableBase.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYGAME_API AHoldableBase : public AInteractableBase
{
	GENERATED_BODY()

public:

	AHoldableBase();

	virtual EInteractableType Interact(AActor* InteractingActor) override;
	
	void OnPickup();

};
