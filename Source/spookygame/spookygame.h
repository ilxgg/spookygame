// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "spookygame.generated.h"

USTRUCT(BlueprintType)
struct FStressStruct
{
	GENERATED_BODY()

	UPROPERTY()
		float NewStressVal;

	UPROPERTY()
		float Duration;

	UPROPERTY()
		float Lifetime;

	FStressStruct()
	{
		NewStressVal = 0;
		Duration = 0;
		Lifetime = 0;
	}

	FStressStruct(float amount, float duration)
	{
		NewStressVal = amount;
		Duration = duration;
		Lifetime = 0;
	}
};
