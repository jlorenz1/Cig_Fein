// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();

	if (Pawn)
	{
		//is valid
		Velocity = Pawn->GetVelocity().Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		
	}

}

void UCharacterAnimation::UseAbilityAnimation(UAnimMontage* AbilityMontage)
{
	if (AbilityMontage)
	{
		Montage_Play(AbilityMontage);
	}
}


void UCharacterAnimation::UseParryAnimation(UAnimMontage * AbilityMontage, float ParryTimeLeft)
{
	if(!AbilityMontage)
	{
		return;
	}

	Montage_Play(AbilityMontage);
}
