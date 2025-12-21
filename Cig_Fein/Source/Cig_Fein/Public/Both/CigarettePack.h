// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CigarettePack.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UCigarettePack : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Back;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Front;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette2;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette3;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette4;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette5;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette6;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette7;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette8;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette9;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette10;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette11;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCigarette* Cigarette12;

	TArray<UCigarette*> Cigarettes;

public:

	void SelectPressed();

	void FlipPressed();

	int32 GetIndex(UCigarette* Cig);

private:

	UPROPERTY()
	UCigarette* CurrentSelected = nullptr;

	UFUNCTION()
	void OnCigaretteSelected(UCigarette* Cig);
	
	void DeleteCigarette(UCigarette* Cig);
};
