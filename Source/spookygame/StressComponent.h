// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StressComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOKYGAME_API UStressComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UStressComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variables")
	uint8 StressMax;

	
	

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnStressUpdate(float StressDecimalAmount); //Called when stress is added or reduced (UI Purposes) argument is percentage of max achievable stress

	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxStress();

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Stress")
		void IncreaseStress(float value); //increase stress by value

	UFUNCTION(BlueprintCallable, Category = "Stress")
		void DecreaseStress(float value); //increase stress by value

	UFUNCTION(BlueprintCallable, Category = "Stress")
		float GetCurrentStress(); //Returns current stress amount as a decimal value out of max achievable stress

protected:



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float StressCurrent;

	UFUNCTION(BlueprintCallable)
	void CheckStressLevel(); //Used to check if stress level is within acceptable range and if stress reaches max






};
