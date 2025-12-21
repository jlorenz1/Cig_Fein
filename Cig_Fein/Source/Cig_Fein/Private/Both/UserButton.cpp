// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/UserButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUserButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonText)
	{
		ButtonText->SetText(InformationText);
	}
}

void UUserButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UUserButton::HandleClickedButton);
	}
}

void UUserButton::HandleClickedButton()
{
	OnClickedEvent.Broadcast();
}

