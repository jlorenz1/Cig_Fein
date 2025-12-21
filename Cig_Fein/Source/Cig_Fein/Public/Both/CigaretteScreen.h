// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CigaretteScreen.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UCigaretteScreen : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarettePack* SelectedPack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* CigaretteTimer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUserButton* SelectButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUserButton* FlipButton;

public:

	UFUNCTION()
	void OnSelectPressed();

	UFUNCTION()
	void OnFlipPressed();

};
