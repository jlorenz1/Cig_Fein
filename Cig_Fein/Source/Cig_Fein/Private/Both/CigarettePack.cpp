// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CigarettePack.h"
#include "Both/Cigarette.h"
#include "Both/UserButton.h"

#include "../Cig_Fein.h"

void UCigarettePack::NativeConstruct()
{
	Super::NativeConstruct();
	
	Cigarettes = { Cigarette1, Cigarette2, Cigarette3, Cigarette4, Cigarette5, Cigarette6, Cigarette7, Cigarette8, Cigarette9, Cigarette10, Cigarette11, Cigarette12 };

	for (UCigarette* Cig : Cigarettes)
	{
		if (Cig)
		{
			Cig->OnSelected.AddDynamic(this, &UCigarettePack::OnCigaretteSelected);
		}
	}
}


void UCigarettePack::SelectPressed()
{
	if (!CurrentSelected) return;

	CurrentSelected->SelectCigarette();
	DeleteCigarette(CurrentSelected);
}

void UCigarettePack::FlipPressed()
{
	if (!CurrentSelected) return;

	CurrentSelected->FlipCigarette();
}

int32 UCigarettePack::GetIndex(UCigarette* Cig)
{

	int32 Index = Cigarettes.IndexOfByKey(Cig);

	if (Index != INDEX_NONE)
	{
		return Index;
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Cigarette not found in the array."));
		return -1;
	}
}

void UCigarettePack::OnCigaretteSelected(UCigarette* Cig)
{

	for (UCigarette* C : Cigarettes)
	{
		if (C != Cig)
			C->Deselect();
	}

	UE_LOG(Game, Warning, TEXT("Cigarette Selected"));

	Cig->Select();
	CurrentSelected = Cig;
}

void UCigarettePack::DeleteCigarette(UCigarette* Cig)
{

	if (!CurrentSelected) return;

	int32 Index = GetIndex(CurrentSelected);
	if (Cigarettes.IsValidIndex(Index))
	{
		UCigarette* SelectedCigarette = Cigarettes[Index];
		Cigarettes.RemoveAt(Index);

		//delete SelectedCigarette
		//SelectedCigarette->RemoveFromParent();
		//CurrentSelected = nullptr;
	}
}
