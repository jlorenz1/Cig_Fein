// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ABaseAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	void HandlePerception(AActor* actor, FAIStimulus stim);

	//----------------------------------------------------------------------//
	// IGenericTeamAgentInterface
	//----------------------------------------------------------------------//
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AIPerception")
	FName PlayerKey;
};
