// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "DoorInteractable.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYGAME_API ADoorInteractable : public AInteractableBase
{
    GENERATED_BODY()

    ADoorInteractable();



protected:

    UFUNCTION(BlueprintImplementableEvent)
    void Open();

public:

    virtual void Interact(AActor* InteractingActor) override;



};
