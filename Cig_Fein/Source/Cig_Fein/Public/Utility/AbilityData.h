// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityData.generated.h"

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AbilityName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> AbilityProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* AbilityAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpiritCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanParry = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsParryable"))
	float ParryDamageMultiplier = 1.5f;

};

