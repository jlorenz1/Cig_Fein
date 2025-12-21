// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Fire_Notify.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UFire_Notify : public UAnimNotify
{
	GENERATED_BODY()

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
