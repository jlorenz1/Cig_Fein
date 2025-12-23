// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Components/CapsuleComponent.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// Sets default values
ABaseAI::ABaseAI() : AFMessage("Action Finished"), HealthKey("HealthRatio")
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void ABaseAI::HandleActionFinished()
{
	FAIMessage message(AFMessage, this, true);

	FAIMessage::Send(this, message);
}

// Called when the game starts or when spawned
void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAI::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);
}


// Called every frame
void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseAI::SetTargetedColorState()
{
	Super::SetTargetedColorState();	
}

void ABaseAI::SetTargetedActor(AActor* NewTarget)
{
	Super::SetTargetedActor(NewTarget);
}

void ABaseAI::HandleHurt(float unused)
{
	Super::HandleHurt(unused);
	//animation
}


