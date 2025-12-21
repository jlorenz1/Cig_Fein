// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SpiritBar;

public:

	UFUNCTION()
	void SetHealthBarPercent(float Percent);

	UFUNCTION()
	void SetSpiritBarPercent(float Percent);

};
