// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Cig_Fein.h"

ABaseAIController::ABaseAIController() :PlayerKey("Player")
{
	UAIPerceptionComponent* AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
	AIPerception->PrimaryComponentTick.bStartWithTickEnabled = false;

	UAISenseConfig_Sight* SenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SenseConfig->SightRadius = 900.f;
	SenseConfig->LoseSightRadius = 1100.f;
	SenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SenseConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SenseConfig->PeripheralVisionAngleDegrees = 45.f;
	SenseConfig->AutoSuccessRangeFromLastSeenLocation = 300.f;
	AIPerception->ConfigureSense(*SenseConfig);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::HandlePerception);
	SetPerceptionComponent(*AIPerception);
}

void ABaseAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	if (BTAsset)
	{
		RunBehaviorTree(BTAsset);
		if (const IGenericTeamAgentInterface* interface = Cast<IGenericTeamAgentInterface>(InPawn))
		{
			SetGenericTeamId(interface->GetGenericTeamId());
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("Failed to get BTAsset"));
	}
}

void ABaseAIController::HandlePerception(AActor* actor, FAIStimulus stim)
{
	UBlackboardComponent* BB = GetBlackboardComponent();

	if (stim.WasSuccessfullySensed())
	{
		BB->SetValueAsObject(PlayerKey, actor);
	}
	else
	{
		BB->ClearValue(PlayerKey);
	}
}

void ABaseAIController::SetGenericTeamId(const FGenericTeamId & NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);

	if (UAIPerceptionComponent* perception = GetPerceptionComponent())
	{
		if (UAIPerceptionSystem* System = UAIPerceptionSystem::GetCurrent(GetWorld()))
		{
			System->UpdateListener(*perception);
		}
	}
}

FGenericTeamId ABaseAIController::GetGenericTeamId() const
{
	if (APawn* pawn = GetPawn())
	{
		if (const IGenericTeamAgentInterface* interface = Cast<IGenericTeamAgentInterface>(pawn))
		{
			return interface->GetGenericTeamId();
		}
	}

	return FGenericTeamId::NoTeam;
}