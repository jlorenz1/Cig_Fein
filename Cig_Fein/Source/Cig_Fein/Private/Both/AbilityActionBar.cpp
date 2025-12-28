// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/AbilityActionBar.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Both/AbilitySlot_HUD.h"

void UAbilityActionBar::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 3; i++)
	{
		FString SlotName = FString::Printf(TEXT("AbilityActionSlot_%d"), i);
		UAbilitySlot_HUD* AbilitySlot = Cast<UAbilitySlot_HUD>(GetWidgetFromName(FName(*SlotName)));
		if (AbilitySlot)
		{
			AbilityActionSlots.Add(AbilitySlot);
		}
	}
}
