// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	SetRootComponent(CollisionComponent);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bIsHomingProjectile = true;


}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapBegin);
	}
}

void ABaseProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor && OtherActor != this && OtherComp)
	{
		// Implement damage or effects on OtherActor here
		if (ImpactShake)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ImpactShake);
		}
		OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
		Destroy();
	}
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Target)
	{
		SetActorTickEnabled(false);
		return;
	}

	
	FVector TargetLocation = Target->GetActorLocation() + FVector(0.f, 0.f, 50.f);
	ProjectileMovementComponent->Velocity = (TargetLocation - GetActorLocation()).GetSafeNormal() * ProjectileSpeed;

	bDistanceToTarget = FVector::Dist(GetActorLocation(), TargetLocation);

	
}

void ABaseProjectile::SetHomingTarget(AActor* TargetActor)
{
	if (ProjectileMovementComponent && TargetActor)
	{
		Target = TargetActor;
		bDistanceToTarget = FVector::Dist(GetActorLocation(), Target->GetActorLocation() + FVector(0.f, 0.f, 50.f));
		ProjectileMovementComponent->HomingTargetComponent = nullptr;
		ProjectileMovementComponent->HomingAccelerationMagnitude = ProjectileSpeed;
		SetActorTickEnabled(true);	
	}
}

