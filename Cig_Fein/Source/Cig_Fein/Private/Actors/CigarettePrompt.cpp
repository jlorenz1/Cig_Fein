// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CigarettePrompt.h"
#include "Components/BoxComponent.h"


// Sets default values
ACigarettePrompt::ACigarettePrompt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void ACigarettePrompt::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACigarettePrompt::BoundOverlap);
	}
}

// Called every frame
void ACigarettePrompt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACigarettePrompt::BoundOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	
}

