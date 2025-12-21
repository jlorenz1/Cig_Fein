// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedEventDel);
/**
 * 
 */
UCLASS()
class CIG_FEIN_API UUserButton : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Variables|Delegate")
	FOnClickedEventDel OnClickedEvent;

protected:


	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FText InformationText;


private:
	UFUNCTION()
	void HandleClickedButton();

};
