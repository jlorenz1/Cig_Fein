// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"    
#include "GameplayTagsManager.h" 
#include "Utility/TargetInterface.h"
#include "ABaseCharacter.generated.h"

UCLASS()
class CIG_FEIN_API AABaseCharacter : public ACharacter, public ITargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	class UAbilityComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Targeting)
	class UTargetComponent* TargetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	class UResourcesComponent* ResourceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapons)
	class UCharacterAnimation* CharacterAnimInst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameplayTags)
	FGameplayTagContainer CharacterTags;
	
	UFUNCTION()
	virtual void HandleHurt(float unusedAmount);

	FGameplayTag Idle;
	FGameplayTag Attacking;
	FGameplayTag Parrying;
	FGameplayTag Stunned;
	FGameplayTag Dead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	//INTERFACE IMPLEMENTATION
	virtual void SetTargetedColorState() override;
	virtual void SetTargetedActor(AActor* NewTarget) override;

	virtual void SetTags(FGameplayTagContainer NewTags)
	{
		CharacterTags = NewTags;
	}

	virtual FGameplayTagContainer GetTags()
	{
		return CharacterTags;
	}


};
