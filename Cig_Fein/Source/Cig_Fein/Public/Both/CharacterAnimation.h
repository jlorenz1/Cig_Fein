// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityAnimate, UAnimMontage*, AbilityMontage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnParryAnimate, UAnimMontage*, AbilityMontage, float, WindowTimeLeft);
/**
 * 
 */
UCLASS()
class CIG_FEIN_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category = "Animation")
	FOnAbilityAnimate OnAbilityUsed;


	UPROPERTY(BlueprintAssignable, Category = "Animation")
	FOnParryAnimate OnParryUsed;


	UFUNCTION()
	void UseAbilityAnimation(UAnimMontage* AbilityMontage);

	UFUNCTION()
	void UseParryAnimation(UAnimMontage* AbilityMontage, float ParryTimeLeft);

protected:

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
	float Direction;

};
