// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Parry_NotifyState.h"
#include "Utility/ParryComponent.h"


void UParry_NotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AActor* owner = MeshComp->GetOwner();

	if (owner)
	{
		if (UParryComponent* parryComp = owner->FindComponentByClass<UParryComponent>())
		{
			ParryComponentRef = parryComp;
			ParryComponentRef->onParryStart(MeshComp->GetSocketLocation("parry_lSocket"));
		}
	}
}

void UParry_NotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (!ParryComponentRef) return;
	if (!ParryComponentRef->CanParry()) return;

	ParryComponentRef->onParryStart(MeshComp->GetSocketLocation("parry_lSocket"));
	
}

void UParry_NotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(!ParryComponentRef)
	{
		return;
	}
	
	ParryComponentRef->OnParry.Broadcast(false);

}
