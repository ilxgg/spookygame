// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "spookygame/StressComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum EPlayerStates
{
	Walking	UMETA(DisplayName="Walking"),
	Running	UMETA(DisplayName = "Running"),
	Hiding	UMETA(DisplayName = "Hiding"),
};

UCLASS()
class SPOOKYGAME_API APlayerCharacter : public ACharacter
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

	void ManageStamina(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

	void LookUp(float value);

	void LookRight(float value);


	UFUNCTION(BlueprintCallable)
	void IncreaseStress(int amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseStress(int amount);

	UFUNCTION(BlueprintCallable)
	EPlayerStates GetPlayerState();


protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player States", meta = (DisplayName = "Player Current State"))
	TEnumAsByte<EPlayerStates> CurrentState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement", meta = (DisplayName = "Running Stamina Drain (per second)"))
	float RunDrain;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement", meta = (DisplayName = "Stamina Regen (per second)"))
		float StaminaRegenRate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Controls", meta = (DisplayName = "Mouse Sensitivity"))
		float SensMulti;
};
