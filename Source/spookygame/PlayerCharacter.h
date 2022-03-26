// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "spookygame/StressComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractionInterface.h"
#include "spookygame\spookygame.h"
#include "PlayerCharacter.generated.h"


UENUM(BlueprintType)
enum EPlayerStates
{
	Walking	UMETA(DisplayName="Walking"),
	Running	UMETA(DisplayName = "Running"),
	Hiding	UMETA(DisplayName = "Hiding"),
};



UCLASS()
class SPOOKYGAME_API APlayerCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStressComponent* StressComponent;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ManageStress(float DeltaTime);

	void ManageStamina(float DeltaTime, bool IsRunning);

	void ManageMovement();

	UFUNCTION(BlueprintCallable)
	void IncreaseStress(float amount); //Increases Stress of player

	UFUNCTION(BlueprintCallable)
	void DecreaseStress(float amount); //Decreases stress of player 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

	void LookUp(float value);

	void LookRight(float value);

	void TryInteract(); // Casts a line trace using Interaction channel to see if hit object is interactable and if so interacts with it

	UFUNCTION(BlueprintCallable)
	void ApplyStress(float amount, float duration);


	UFUNCTION(BlueprintCallable)
	EPlayerStates GetPlayerState(); //returns the player's state

	UFUNCTION(BlueprintCallable)
	EInteractableType Interact(AActor* InteractingActor) override; //Function used when an object interacts with the player


protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player States", meta = (DisplayName = "Player Current State"))
	TEnumAsByte<EPlayerStates> CurrentState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement", meta = (DisplayName = "Running Stamina Drain (per second)"))
	float RunDrain; //Amount of stamina per second drained when running

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement", meta = (DisplayName = "Stamina Regen (per second)"))
	float StaminaRegenRate; //amount of stamina regained per second

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stress", meta = (DisplayName = "Stress loss when hiding (per second)"))
	float StressHidingDecrease;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controls", meta = (DisplayName = "Mouse Sensitivity"))
	float SensMulti; //sensistivity multiplier for changing in game sensitivity

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Controls", meta = (DisplayName = "Interact Range"))
	float InteractRange; //distance that the player can be from an object in order to interact with it

	bool bPlayerInitialHide;

	TArray<FStressStruct> StressPool;

};

