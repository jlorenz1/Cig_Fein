// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityState.generated.h"


UENUM(BlueprintType)
enum class EAbilityWeaponType : uint8
{
	HandCannon UMETA(DisplayName = "HandCannon"),
	Sword UMETA(DisplayName = "Sword")
};



USTRUCT(BlueprintType)
struct FAbilityState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityWeaponType weaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float cooldownRemaining;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	int charges;

};


