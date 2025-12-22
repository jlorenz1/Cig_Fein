// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseAI.h"
#include "Slime_AI.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API ASlime_AI : public ABaseAI
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ASlime_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PA_Component)
	class USlimePA_Component* SlimePAComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleHurt(float unused) override;
};
