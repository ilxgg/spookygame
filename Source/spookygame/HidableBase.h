// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "HidableBase.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYGAME_API AHidableBase : public AInteractableBase
{
	GENERATED_BODY()

public:

	AHidableBase();

	UPROPERTY(EditAnywhere, BLueprintReadOnly)
	USceneComponent* HideLocation;

	UPROPERTY(EditAnywhere, BLueprintReadOnly)
	USceneComponent* ExitLocation;

	
protected:

	bool bIsHidingActor;

	void Hide(AActor* HidingActor);

	void EndHide(AActor* HidingActor);


public:

	virtual EInteractableType Interact(AActor* InteractingActor)override;
};
