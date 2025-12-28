// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityActionBar.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UAbilityActionBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox_ActionBar;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_ActionSlot;

	UPROPERTY(meta= (BindWidget))
	class UAbilitySlot_HUD* AbilityActionSlot_0;

	UPROPERTY(meta = (BindWidget))
	class UAbilitySlot_HUD* AbilityActionSlot_1;

	UPROPERTY(meta = (BindWidget))
	class UAbilitySlot_HUD* AbilityActionSlot_2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Action Bar")
	TArray<UAbilitySlot_HUD*> AbilityActionSlots;


};
