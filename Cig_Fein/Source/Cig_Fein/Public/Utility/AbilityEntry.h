// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utility/AbilityData.h"
#include "Utility/AbilityState.h"
#include "AbilityEntry.generated.h"

USTRUCT(BlueprintType)
struct FAbilityEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAbilityData abilityData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FAbilityState abilityState;
};
