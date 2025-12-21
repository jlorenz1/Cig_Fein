// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utility/AbilityEntry.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityUsed, int32, AbilityIndex, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityFired);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CIG_FEIN_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	FOnAbilityUsed OnAbilityUsed;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	FOnAbilityFired OnAbilityFired;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TMap<int32, FAbilityEntry> Abilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	FVector CastLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UCharacterAnimation* AnimationRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UResourcesComponent* ResourceRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	AActor* TargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FAbilityEntry CurrentAbility;

	bool bActionInProgress = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void UseAbility(int32 AbilitySlot, AActor* Target);

	void SetCastLocation(FVector NewLocation) {
		CastLocation = NewLocation;
	}

	void SetAnimationRef(UCharacterAnimation* NewAnimationRef) {
		AnimationRef = NewAnimationRef;
	}

	void SetResourceRef(UResourcesComponent* NewResourceRef) {
		ResourceRef = NewResourceRef;
	}

	FVector GetSpawnLocation();

	bool CheckIfAbilityOnCooldown(int32 AbilitySlot);
private:

	void StopMovementDuringAbility();

	UFUNCTION()
	void SpawnCurrentAbilityFromNotify();

	bool CheckSpellRange(int32 AbilitySlot, FVector ActorLocation);	

	bool CheckResources(int32 AbilitySlot);
};
