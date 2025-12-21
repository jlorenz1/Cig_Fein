// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/Cigarette.h"
#include "Components/SizeBox.h"
#include "Animation/UMGSequencePlayer.h"

#include "../Cig_Fein.h"

void UCigarette::NativeConstruct()
{
	Super::NativeConstruct();

	if (CollisionPosition)
	{
		InitialPosition = FVector2D(CollisionPosition->GetRenderTransform().Translation);
		CurrentPosition = InitialPosition;
		CurrentRotation = CollisionPosition->GetRenderTransformAngle();
	}
}

void UCigarette::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CollisionPosition) return;

	if (bPicked)
	{
		


	

	}
	else
	{
		PickedAlpha = 0.f;
		if (bSelected)
		{
			FVector2D Target = bSelected ? InitialPosition + Offset : InitialPosition;
			CurrentPosition = FMath::Vector2DInterpTo(CurrentPosition, Target, InDeltaTime, LerpSpeed);
			CollisionPosition->SetRenderTranslation(CurrentPosition);
			return;
		}

		FVector2D Target = bHovered ? InitialPosition + Offset : InitialPosition;
		CurrentPosition = FMath::Vector2DInterpTo(CurrentPosition, Target, InDeltaTime, LerpSpeed);
		CollisionPosition->SetRenderTranslation(CurrentPosition);
	}
}

void UCigarette::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (!CollisionPosition) return;
	if (bHovered) return;

	bHovered = true;
}

void UCigarette::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (!CollisionPosition) return;
	if (!bHovered) return;

	bHovered = false;
}

FReply UCigarette::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	NotifySelected();
	return FReply::Handled();
}

void UCigarette::Select()
{
	bSelected = true;
	bHovered = false;
}

void UCigarette::Deselect()
{
	bSelected = false;
	bHovered = false;
}

void UCigarette::FlipCigarette()
{
	bFlipped = CurrentRotation >= 180.f;

	if (FlipCigaretteAnimation && !bFlipped)
	{
		PlayAnimation(FlipCigaretteAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		CurrentRotation = CollisionPosition->GetRenderTransformAngle() + 180.f;
	}
	else if (FlipCigaretteAnimation && bFlipped)
	{
		PlayAnimation(FlipCigaretteAnimation, 0.f, 1, EUMGSequencePlayMode::Reverse, 1.f);
		CurrentRotation = CollisionPosition->GetRenderTransformAngle() - 180.f;
	}
}

void UCigarette::SelectCigarette()
{
	if (bFlipped) return;

	bSelected = false;
	bHovered = false;
	bPicked = true;
}

