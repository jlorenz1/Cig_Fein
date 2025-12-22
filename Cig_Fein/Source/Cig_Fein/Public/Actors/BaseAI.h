// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"	
#include "ABaseCharacter.h"
#include "BaseAI.generated.h"

UCLASS()
class CIG_FEIN_API ABaseAI : public AABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//INTERFACE IMPLEMENTATION
	virtual void SetTargetedColorState() override;
	virtual void SetTargetedActor(AActor* NewTarget) override;

	virtual void HandleHurt(float unused) override;

};
