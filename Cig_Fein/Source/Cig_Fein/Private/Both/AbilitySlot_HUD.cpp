// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/AbilitySlot_HUD.h"
#include "Both/AbilityUtility_HUD.h"
#include "Components/SizeBox.h"	

void UAbilitySlot_HUD::SetAbilityUtilityText(const FString& NewText)
{
	if (AbilityUtilityWidget)
	{
		AbilityUtilityWidget->SetAbilityUtilityText(NewText);
	}
}

void UAbilitySlot_HUD::ResetAbilityUtilityText()
{
	if (AbilityUtilityWidget)
	{
		AbilityUtilityWidget->ResetAbilityUtilityText();
	}
}