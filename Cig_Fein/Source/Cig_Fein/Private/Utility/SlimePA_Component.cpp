// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SlimePA_Component.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USlimePA_Component::USlimePA_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void USlimePA_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USlimePA_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!MeshReference) return;

    
    FVector Velocity = CMC_Reference->Velocity;
    float Speed = Velocity.Size2D();
   
    if (CMC_Reference->IsMovingOnGround())
    {
        SquishTime += DeltaTime * SquishSpeed * (Speed / 600.0f);

        float SquishFactor = FMath::Sin(SquishTime) * SquishAmount;
        FVector NewScale = OriginalScale;
        NewScale.Z = OriginalScale.Z * (1.0f - SquishFactor * VerticalSquishIntensity);
        NewScale.X = OriginalScale.X * (1.0f + SquishFactor * HorizontalSquishIntensity);
        NewScale.Y = OriginalScale.Y * (1.0f + SquishFactor * ZSquishIntensity);

        MeshReference->SetRelativeScale3D(NewScale);
    }
    else
    {
        //reset if not moving
        FVector CurrentScale = MeshReference->GetRelativeScale3D();
        FVector LerpedScale = FMath::VInterpTo(CurrentScale, OriginalScale, DeltaTime, 5.0f);
        MeshReference->SetRelativeScale3D(LerpedScale);

        SquishTime = 0.0f;
    }

	// ...
}

void USlimePA_Component::SetupMeshReference(USkeletalMeshComponent* NewMesh)
{
    MeshReference = NewMesh;

    if (MeshReference)
    {
        OriginalScale = MeshReference->GetRelativeScale3D();
		SetComponentTickEnabled(true);
	}
}

