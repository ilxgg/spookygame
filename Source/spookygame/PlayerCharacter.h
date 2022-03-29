// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "spookygame/StressComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractionInterface.h"
#include "spookygame\spookygame.h"
#include "StaminaComponent.h"
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
	UStressComponent* StressComponent; //Component used to measure and modify the player's stress

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaminaComponent* StaminaComponent; //Component used to allow player to sprint 



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ManageStress(float DeltaTime); //called per tick to manage the player's stress 

	void ManageStamina(float DeltaTime, bool IsRunning); //called per tick to manage the stamina of the player depending if the player is running or not

	void ManageMovement(float DeltaTime); //called per tick to manage the movement using players state and should correct it accordingly

	UFUNCTION(BlueprintCallable)
	void IncreaseStress(float amount); //Increases Stress of player

	UFUNCTION(BlueprintCallable)
	void DecreaseStress(float amount); //Decreases stress of player 

	UFUNCTION(BlueprintCallable)
	void DisableMovement(); //diables player movement

	UFUNCTION(BlueprintCallable)
	void EnableMovement(); //enables player movement

	void ChangeState(EPlayerStates newState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

	void LookUp(float value);

	void LookRight(float value);

	void TrySprint();

	void EndSprint();

	void TryInteract(); // Casts a line trace using Interaction channel to see if hit object is interactable and if so interacts with it

	UFUNCTION(BlueprintCallable)
	void ApplyStress(float amount, float duration); //Adds stress to player's stress pool, added as amount over duration


	UFUNCTION(BlueprintCallable)
	EPlayerStates GetPlayerState(); //returns the player's state

	UFUNCTION(BlueprintCallable)
	EInteractableType Interact(AActor* InteractingActor) override; //Function used when an object interacts with the player


protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player States", meta = (DisplayName = "Player Current State"))
	TEnumAsByte<EPlayerStates> CurrentState; //Player's current state, determines player behaviour

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stress", meta = (DisplayName = "Stress loss when hiding (per second)"))
	float StressHidingDecrease; //stress decrease per second whilst the player is hiding

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controls", meta = (DisplayName = "Mouse Sensitivity"))
	float SensMulti; //sensistivity multiplier for changing in game sensitivity

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Controls", meta = (DisplayName = "Interact Range"))
	float InteractRange; //distance that the player can be from an object in order to interact with it

	bool bPlayerInitialHide; //used for when player initially hides

	TArray<FStressStruct> StressPool; //contains all the stress that needs to be added to the player

	bool bIsMovementEnabled; //used to disable and enable walking and running

	bool SprintToggle; //used to determine if sprinting is press and hold or toggle type

	bool SprintToggleSecondRelease; //used when sprint mode is set to toggle, every 2nd release stops sprinting

};

