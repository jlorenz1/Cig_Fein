// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHUD.h"
#include "Components/ProgressBar.h"

void UPlayerHUD::SetHealthBarPercent(float Percent)
{
	if (!HealthBar) return;
	HealthBar->SetPercent(Percent);
}

void UPlayerHUD::SetSpiritBarPercent(float Percent)
{
	if (!SpiritBar) return;
	SpiritBar->SetPercent(Percent);
}
