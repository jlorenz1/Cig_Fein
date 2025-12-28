// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Slime_AI.h"

#include "Utility/SlimePA_Component.h"

ASlime_AI::ASlime_AI()
{
	SlimePAComponent = CreateDefaultSubobject<USlimePA_Component>(TEXT("SlimePAComponent"));
}

void ASlime_AI::BeginPlay()
{
	Super::BeginPlay();
}

void ASlime_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SlimePAComponent)
	{
		SlimePAComponent->SetupMeshReference(GetMesh());
	}
}

void ASlime_AI::HandleHurt(float unused)
{

}
