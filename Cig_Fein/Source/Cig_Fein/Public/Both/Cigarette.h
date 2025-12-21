// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cigarette.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCigaretteSelected, UCigarette*, Cig);
/**
 * 
 */
UCLASS()
class CIG_FEIN_API UCigarette : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCigaretteSelected OnSelected;

	UFUNCTION(BlueprintCallable)
	void Select();

	UFUNCTION(BlueprintCallable)
	void Deselect();

	UFUNCTION(BlueprintCallable)
	void FlipCigarette();

	UFUNCTION(BlueprintCallable)
	void SelectCigarette();

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Cig;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USizeBox* CollisionPosition;



	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	void NotifySelected() { OnSelected.Broadcast(this); };

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FlipCigaretteAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SelectCigaretteAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector2D InitialPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	FVector2D Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	FVector2D BurnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float LerpSpeed;

	FVector2D CurrentPosition;
	float CurrentRotation = 0.f;

	float PickedAlpha = 0.f;
	float PickedLerpSpeed = 2.f;
	float PickedAmplitude = 120.f;

	bool bHovered;
	bool bSelected;
	bool bFlipped;
	bool bPicked;


	
};
