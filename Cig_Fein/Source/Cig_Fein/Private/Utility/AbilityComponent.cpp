 // Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/AbilityComponent.h"
#include "Utility/ResourcesComponent.h"

#include "Both/CharacterAnimation.h"

#include "Actors/BaseProjectile.h"
#include "Actors/CharacterInput.h"

#include "Containers/Queue.h"

#include "../Cig_Fein.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	OnAbilityUsed.AddDynamic(this, &UAbilityComponent::UseAbility);
	OnAbilityFired.AddDynamic(this, &UAbilityComponent::SpawnCurrentAbilityFromNotify);

	AActor* owner = GetOwner();
	if (owner)
	{
		OwnerActor = owner;
	}
	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bAnyCooldownsActive = false;

	for (auto& Elem : Abilities)
	{
		FAbilityEntry& AbilityEntry = Elem.Value;

		if (AbilityEntry.abilityState.cooldownRemaining > 0.f)
		{
			AbilityEntry.abilityState.cooldownRemaining = FMath::Max(0.f, AbilityEntry.abilityState.cooldownRemaining - DeltaTime);

			if (AbilityEntry.abilityState.cooldownRemaining <= 0.f)
			{
				AbilityEntry.abilityState.bIsActive = false;
				UE_LOG(LogTemp, Warning, TEXT("Ability %s is ready to use."), *AbilityEntry.abilityData.AbilityName.ToString());
			}

			if (AbilityEntry.abilityState.cooldownRemaining > 0.f)
			{
				bAnyCooldownsActive = true;
			}
		}
	}

	SetComponentTickEnabled(bAnyCooldownsActive);
	
	// ...
}

void UAbilityComponent::UseAbility(int32 AbilitySlot, AActor* Target)
{
	if (!AnimationRef) return; if (!ResourceRef) return;

	if (Abilities.Contains(AbilitySlot) && Target && CheckSpellRange(AbilitySlot, Target->GetActorLocation()) && CheckResources(AbilitySlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("Using Ability in Slot: %d"), AbilitySlot);

		CurrentAbility = Abilities[AbilitySlot];
		TargetActor = Target;

		Abilities[AbilitySlot].abilityState.cooldownRemaining = CurrentAbility.abilityData.Cooldown;
		
		SetComponentTickEnabled(true);

		if (Abilities[AbilitySlot].abilityState.weaponType == EAbilityWeaponType::HandCannon)
		{
			AnimationRef->OnAbilityUsed.Broadcast(Abilities[AbilitySlot].abilityData.AbilityAnimation);
			ResourceRef->OnSpiritChange.Broadcast(Abilities[AbilitySlot].abilityData.SpiritCost);
			
			StopMovementDuringAbility();
		}
		else if (Abilities[AbilitySlot].abilityState.weaponType == EAbilityWeaponType::Sword)
		{
			AnimationRef->OnAbilityUsed.Broadcast(Abilities[AbilitySlot].abilityData.AbilityAnimation);
		}
	}
}

bool UAbilityComponent::CheckIfAbilityOnCooldown(int32 AbilitySlot)
{
	if (Abilities.Contains(AbilitySlot))
	{
		if (Abilities[AbilitySlot].abilityState.cooldownRemaining > 0.f)
		{
			return true;
		}
	}

	return false;
}

void UAbilityComponent::StopMovementDuringAbility()
{
	if (!OwnerActor) return;
	if(!TargetActor) return;

	FVector MyPos = OwnerActor->GetActorLocation();
	FVector TargetPos = TargetActor->GetActorLocation();

	FRotator targetRot = FRotationMatrix::MakeFromX(TargetPos - MyPos).Rotator();
	OwnerActor->SetActorRotation(targetRot);

	ACharacterInput* Char = Cast<ACharacterInput>(OwnerActor);
	if (!Char) return;
	Char->StopAllMovement();
}

void UAbilityComponent::SpawnCurrentAbilityFromNotify()
{

	if (CurrentAbility.abilityData.AbilityProjectileClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = Cast<APawn>(OwnerActor);
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector SpawnLocation = CastLocation;
		FRotator SpawnRotation = OwnerActor->GetActorForwardVector().Rotation();

		AActor* Projectile = GetWorld()->SpawnActor<AActor>(
			CurrentAbility.abilityData.AbilityProjectileClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);

		DrawDebugSphere(GetWorld(), SpawnLocation, 10, 12, FColor::Red, false, 5.f);

		ABaseProjectile* BaseProjectile = Cast<ABaseProjectile>(Projectile);

		if (BaseProjectile)
		{
			BaseProjectile->SetFiringActor(OwnerActor);
			BaseProjectile->SetHomingTarget(TargetActor);
		}
		else
		{
			UE_LOG(Game, Warning, TEXT("Failed to spawn projectile."));
		}
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("No Projectile Class assigned to this ability."));
	}
}

bool UAbilityComponent::CheckSpellRange(int32 AbilitySlot, FVector ActorLocation)
{
	if (Abilities.Contains(AbilitySlot) && OwnerActor)
	{
		float distanceToTarget = FVector::Dist(OwnerActor->GetActorLocation(), ActorLocation);

		return distanceToTarget <= Abilities[AbilitySlot].abilityData.Range;
	}

	return false;
}

bool UAbilityComponent::CheckResources(int32 AbilitySlot)
{
	if (ResourceRef && Abilities.Contains(AbilitySlot))
	{
		float currentSpirit = ResourceRef->GetCurrentSpirit();
		float abilityCost = Abilities[AbilitySlot].abilityData.SpiritCost;
		if (currentSpirit >= abilityCost)
		{
			return true;
		}
		else
		{
			UE_LOG(Game, Warning, TEXT("Not enough spirit to use ability."));
		}
	}

	return false;
}

