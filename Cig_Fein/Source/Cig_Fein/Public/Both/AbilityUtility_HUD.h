// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityUtility_HUD.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UAbilityUtility_HUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AbilityUtilityText;

public:

	void SetAbilityUtilityText(const FString& NewText);
	void ResetAbilityUtilityText();
};
