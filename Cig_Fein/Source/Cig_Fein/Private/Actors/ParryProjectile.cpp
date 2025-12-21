// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ParryProjectile.h"
#include "Actors/CharacterInput.h"
#include "Utility/ParryComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"

#include "../Cig_Fein.h"
AParryProjectile::AParryProjectile()
{

}

void AParryProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!ProjectileMesh)
    {
        return;
	}

    if (bCanParry)
    {
        if (bDistanceToTarget <= bParryWindowDistanceMax && bDistanceToTarget >= bParryWindowDistanceMin)
        {
            ProjectileMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0.f, 1.f, 0.f));
        }
        else
        {

            ProjectileMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.f, 0.f, 0.f)); // Red
        }
    }
    
}

void AParryProjectile::SetHomingTarget(AActor* TargetActor)
{
	Super::SetHomingTarget(TargetActor);
    
    ProjectileMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.f, 0.f, 0.f)); // Red

    UParryComponent* Parry = Target->FindComponentByClass<UParryComponent>();
    bCanParry = (Parry != nullptr);
}

void AParryProjectile::GetParried(AActor* NewOwner)
{
    const FVector EscapeDir = (GetActorLocation() - NewOwner->GetActorLocation()).GetSafeNormal();

    if (ProjectileMovementComponent)
    {
        ProjectileMovementComponent->Velocity = EscapeDir * ProjectileSpeed;
    }

    HitReacts--;

    AActor* OriginalFiringActor = FiringActor;

	FiringActor = NewOwner;
    SetFiringActor(NewOwner);
    SetInstigator(Cast<APawn>(NewOwner));

    if (OriginalFiringActor)
    {
		//UE_LOG(Game, Log, TEXT("Resetting Homing Target to %s"), *OriginalFiringActor->GetName());
        SetHomingTarget(OriginalFiringActor);
    }
}

void AParryProjectile::BeginPlay()
{
	Super::BeginPlay();

	bWindowTimeLeft = bParryWindowDistanceMax;
}

void AParryProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (!OtherActor || OtherActor == FiringActor)
    {
        return;
    }


    if (OtherActor->ActorHasTag("AI"))
    {
        if(HitReacts > 0)
        {
            HitReacts--;
            GetParried(OtherActor);
            OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
            Damage *= ParryDamageMultiplier;
            return;
        }

    }

	Damage *= ParryDamageDamp;
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
