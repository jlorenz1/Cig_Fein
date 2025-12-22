// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseAI::ABaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

// Called when the game starts or when spawned
void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

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


