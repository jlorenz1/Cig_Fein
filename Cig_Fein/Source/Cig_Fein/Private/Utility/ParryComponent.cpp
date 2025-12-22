// Fill out your copyright notice in the Description page of Project Settings.

#include "Utility/ParryComponent.h"

#include "Actors/ParryProjectile.h"
#include "Actors/CharacterInput.h"

#include "Components/BoxComponent.h"   
#include "Kismet/GameplayStatics.h"

#include "Both/CharacterAnimation.h"

#include "Camera/CameraShakeBase.h"
#include "../Cig_Fein.h"
// Sets default values for this component's properties
UParryComponent::UParryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UParryComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	if (owner)
	{
		OwnerActor = owner;
	}



	OnParrySuccess.AddDynamic(this, &UParryComponent::ParryClosestActor);
	OnParry.AddDynamic(this, &UParryComponent::SetParryBoxCollisions);
	OnParry.Broadcast(false);
	// ...
	
}


// Called every frame
void UParryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	// ...
}

void UParryComponent::StartParry()
{
	if (!OwnerActor)
	{
		UE_LOG(Game, Warning, TEXT("Owner Actor Not Found"));	
		return;
	}

	ACharacterInput* Char = Cast<ACharacterInput>(OwnerActor);
	if (!Char)
	{
		UE_LOG(Game, Warning, TEXT("Owner Actor Not of Type CharacterInput"));
		return;
	}



	AParryProjectile* CParryActor = Cast<AParryProjectile>(GetClosestParrableActor());

	if (AnimationRef && ParryAnimation)
	{
		if(bParryHappening)
			return;

		if (CParryActor)
		{
			FRotator NewRotation = (CParryActor->GetActorLocation() - OwnerActor->GetActorLocation()).Rotation();
			NewRotation.Roll = 0.0f;
			NewRotation.Pitch = 0.0f;

			OwnerActor->SetActorRotation(NewRotation);
			Char->StopAllMovement();
			AnimationRef->OnParryUsed.Broadcast(ParryAnimation, CParryActor->GetWindowTimeLeft());
			bParryHappening = true;
		}
		
	}
}

void UParryComponent::onParryStart(FVector SocketLocation)
{
	OnParry.Broadcast(true);
}

void UParryComponent::onParryEnd()
{

	bParryHappening = false;
	GetWorld()->GetTimerManager().ClearTimer(ParryTimer);
	SetParryBoxCollisions(false);

}

bool UParryComponent::CanParry()
{
	return bCanParry;
}


void UParryComponent::SetParryBoxCollisions(bool bStart)
{
	if (bStart)
	{
		bCanParry = true;
	}
	else
	{
		bCanParry = false;
		bParryHappening = false;
		GetWorld()->GetTimerManager().ClearTimer(ParryTimer);
		return;
	}


	FVector Center = OwnerActor->GetActorLocation();

	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(ParryRadius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor);

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Center, Center, FQuat::Identity, ECC_GameTraceChannel1, Sphere, QueryParams);

	if (!bHit)
	{
		bParryHappening = false;
		return;
	}

	bool bSuccessfulParry = false;

	for (FHitResult Hit : HitResults)
	{
		AParryProjectile* Projectile = Cast<AParryProjectile>(Hit.GetActor());
		if (!Projectile) continue;

		if (Projectile->IsInParryWindow(GetOwner()->GetActorLocation()))
		{
			SlowWorldOnParry();

			if(ParryCameraShake)
			{
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ParryCameraShake);
			}

			Projectile->GetParried(GetOwner());

			bParryHappening = false;
			bCanParry = false;
			bSuccessfulParry = true;
			break;
		}

	}

	if (!bSuccessfulParry)
	{
		GetWorld()->GetTimerManager().SetTimer(ParryTimer, this, &UParryComponent::ResetParry, ParryCooldown, false);
	}
}

AActor* UParryComponent::GetClosestParrableActor()
{
	if(ClosestParryActor)
		ClosestParryActor = nullptr;

	//Sphere trace for parryable projectiles
	
	if (!OwnerActor) return nullptr;

	FVector Center = OwnerActor->GetActorLocation();

	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(CheckRadius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor);

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Center, Center, FQuat::Identity, ECC_GameTraceChannel1, Sphere, QueryParams);

	if (bHit)
	{
		float ClosestDistance = CheckRadius;

		for (const FHitResult& Hit : HitResults)
		{
			AParryProjectile* ParryProj = Cast<AParryProjectile>(Hit.GetActor());
			if (ParryProj)
			{
				if(ParryProj->GetOwner() == OwnerActor)
					continue;

				float Distance = FVector::Dist(OwnerActor->GetActorLocation(), ParryProj->GetActorLocation());
				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestParryActor = ParryProj;
				}
			}
		}
	}

	if(ClosestParryActor)
	{
		float dist = FVector::Dist(OwnerActor->GetActorLocation(), ClosestParryActor->GetActorLocation());
		UE_LOG(Game, Log, TEXT("Closest Parrable Actor: %s at Distance: %f"), *ClosestParryActor->GetName(), dist);
	}
	
	return ClosestParryActor;
}

void UParryComponent::SlowWorldOnParry()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.05f);

	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [this]() {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		}, 0.009f, false);
}

void UParryComponent::ParryClosestActor()
{
	if (!ParryingActor) return;

	AParryProjectile* ParryProj = Cast<AParryProjectile>(ParryingActor);

	if(ParryProj)
	{
		ParryProj->GetParried(OwnerActor);
	}
}

void UParryComponent::ResetParry()
{
	bParryHappening = false;
}

