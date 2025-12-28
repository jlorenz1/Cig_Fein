// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySlot_HUD.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UAbilitySlot_HUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UAbilityUtility_HUD* AbilityUtilityWidget;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* AbilityUtilitySizeBox;

public:

	void SetAbilityUtilityText(const FString& NewText);
	void ResetAbilityUtilityText();
};
