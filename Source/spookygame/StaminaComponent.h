// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOKYGAME_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CheckStamina(); //Makes sure stamina is in acceptable range

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; 

	UFUNCTION(BlueprintCallable)
	float getCurrentStamina(); //Returns amount of stamina out of max in a 0-1 range

	void ManageStamina(float DeltaTime, bool IsRunning); //called to increase or decrease the stamina from the parent actor class

	bool canSprint();

	UFUNCTION(BlueprintCallable)
	float getMovementSpeed(bool IsRunning);

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Stamina")
	float StaminaMax;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Stamina")
	float StaminaCurrent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Stamina", meta = (DisplayName = "Running Stamina Drain (per second)"))
	float RunningStaminaDrain;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Stamina", meta = (DisplayName = "Stamina Regen (per second)"))
	float StaminaRegen;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "Stamina", meta = (DisplayName = "Running Speed"))
	float RunningSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Stamina", meta = (DisplayName = "Walking Speed"))
	float WalkSpeed;

	bool bCanRun;


};
