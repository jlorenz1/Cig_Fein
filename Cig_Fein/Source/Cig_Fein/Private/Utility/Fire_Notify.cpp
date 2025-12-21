// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Fire_Notify.h"
#include "Utility/AbilityComponent.h"

void UFire_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		AActor* actor = MeshComp->GetOwner();
		if (actor)
		{
			UAbilityComponent* abilityComp = actor->FindComponentByClass<UAbilityComponent>();
			if (abilityComp)
			{
				abilityComp->OnAbilityFired.Broadcast();
			}
		}
	}
}
