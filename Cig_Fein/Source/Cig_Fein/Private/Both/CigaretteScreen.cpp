// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CigaretteScreen.h"
#include "Both/CigarettePack.h"
#include "Both/Cigarette.h"
#include "Components/ProgressBar.h"
#include "Both/UserButton.h"

#include "../Cig_Fein.h"

void UCigaretteScreen::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectButton)
	{
		SelectButton->OnClickedEvent.AddDynamic(this, &UCigaretteScreen::OnSelectPressed);
	}

	if (FlipButton)
	{
		FlipButton->OnClickedEvent.AddDynamic(this, &UCigaretteScreen::OnFlipPressed);
	}

	if (CigaretteTimer)
	{
		CigaretteTimer->SetPercent(1.f);
		CigaretteTimer->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCigaretteScreen::OnSelectPressed()
{
	if (SelectedPack)
	{
		SelectedPack->SelectPressed();
	}

	if (CigaretteTimer)
	{
		CigaretteTimer->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCigaretteScreen::OnFlipPressed()
{
	if (SelectedPack)
	{
		UE_LOG(Game, Warning, TEXT("Flip Pressed"));
		SelectedPack->FlipPressed();
	}
}
