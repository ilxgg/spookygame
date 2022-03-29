// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "Components\BoxComponent.h"
#include "InteractableBase.generated.h"


UCLASS()
class SPOOKYGAME_API AInteractableBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* InteractionVolume;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TEnumAsByte<EInteractableType> InteractionType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual EInteractableType Interact(AActor* InteractingActor) override;

	

};
