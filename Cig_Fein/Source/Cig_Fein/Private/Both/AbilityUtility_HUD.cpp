// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/AbilityUtility_HUD.h"
#include "Components/TextBlock.h"	

void UAbilityUtility_HUD::SetAbilityUtilityText(const FString& NewText)
{
	if (AbilityUtilityText)
	{
		AbilityUtilityText->SetText(FText::FromString(NewText));
	}
}

void UAbilityUtility_HUD::ResetAbilityUtilityText()
{
}
