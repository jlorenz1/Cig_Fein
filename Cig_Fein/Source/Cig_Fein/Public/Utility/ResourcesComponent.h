// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourcesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceChange, float, bAmount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CIG_FEIN_API UResourcesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourcesComponent();

	UPROPERTY(BlueprintReadOnly, Category = "Resources")
	FOnResourceChange OnHealthChange;

	UPROPERTY(BlueprintReadOnly, Category = "Resources")
	FOnResourceChange OnSpiritChange;

	UPROPERTY(BlueprintReadOnly, Category = "Resources")
	FOnResourceChange OnHealthChangeHUD;

	UPROPERTY(BlueprintReadOnly, Category = "Resources")
	FOnResourceChange OnSpiritChangeHUD;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float MaxSpirit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	float CurrentSpirit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float HealthRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float SpiritRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	bool bCanRegenResources = false;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetHealth(float NewHealth);
	UFUNCTION()
	void SetSpirit(float NewSpirit);

	float GetCurrentHealth() const { return CurrentHealth; };
	float GetCurrentSpirit() const { return CurrentSpirit; };
};
