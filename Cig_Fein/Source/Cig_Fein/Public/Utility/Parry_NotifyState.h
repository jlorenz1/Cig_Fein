// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Parry_NotifyState.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API UParry_NotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parry")
	class UParryComponent* ParryComponentRef;

};
