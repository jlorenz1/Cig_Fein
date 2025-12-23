// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"	
#include "GenericTeamAgentInterface.h"
#include "ABaseCharacter.h"
#include "BaseAI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionFinishedDelegate);
UCLASS()
class CIG_FEIN_API ABaseAI : public AABaseCharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAI();

	UFUNCTION()
	void HandleActionFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FOnActionFinishedDelegate actionFinishedDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AFMessage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName HealthKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Team)
	uint8 TeamID;

	virtual void PossessedBy(class AController* controller) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//INTERFACE IMPLEMENTATION

	//----------------------------------------------------------------------//
	// ITargetInterface
	//----------------------------------------------------------------------//
	virtual void SetTargetedColorState() override;
	virtual void SetTargetedActor(AActor* NewTarget) override;

	virtual void HandleHurt(float unused) override;

	//----------------------------------------------------------------------//
	// IGenericTeamAgentInterface
	//----------------------------------------------------------------------//

	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

};
