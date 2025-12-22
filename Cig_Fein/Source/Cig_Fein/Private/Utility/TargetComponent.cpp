// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/TargetComponent.h"
#include "Utility/TargetInterface.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	if(owner)
	{
		OwnerActor = owner;
	}

	ACharacter* character = Cast<ACharacter>(OwnerActor);
	if (!character) return;

	USkeletalMeshComponent* mesh = character->GetMesh();
	if (!mesh) return;

	UMaterialInterface* mat = mesh->GetOverlayMaterial();
	if (!mat) return;

	//set color parameter
	if (!mat->IsA<UMaterialInstanceDynamic>())
	{
		OutlineMID = UMaterialInstanceDynamic::Create(mat, this);
		if (!OutlineMID) return;

		mesh->SetOverlayMaterial(OutlineMID);
	}

	SetColorState(UnTargetedColorState);
	// ...
	
}


// Called every frame
void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTargetComponent::SetTargeted()
{
	bIsTargeted = !bIsTargeted;

	if(bIsTargeted)
	{
		SetColorState(TargetedColorState);
	}
	else
	{
		SetColorState(UnTargetedColorState);
	}
}

void UTargetComponent::ClearTargetActor()
{
	if (!TargetActor) return;

	if(TargetActor->Implements<UTargetInterface>())
	{
		ITargetInterface* targetInterface = Cast<ITargetInterface>(TargetActor);
		if (targetInterface)
		{
			targetInterface->SetTargetedColorState();
			TargetActor = nullptr;
		}
	}

}

void UTargetComponent::SetTargetingActor(AActor* NewTarget)
{
	if (!NewTarget) return;

	if(TargetActor)
	{
		ClearTargetActor();
	}

	TargetActor = NewTarget;
	
}

void UTargetComponent::SetColorState(FLinearColor ColorState)
{
	if (OutlineMID)
	{
		OutlineMID->SetVectorParameterValue(TEXT("Color"), ColorState);
	}
}





