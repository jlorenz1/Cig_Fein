// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlimePA_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CIG_FEIN_API USlimePA_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlimePA_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = References)
	class USkeletalMeshComponent* MeshReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = References)
	class UCharacterMovementComponent* CMC_Reference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SQT)
	float SquishTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SQT)
	float SquishSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SQT)
	float SquishAmount = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SQT)
	float VerticalSquishIntensity = 0.33f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SQT)
	float HorizontalSquishIntensity = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SQT)
	float ZSquishIntensity = 0.35f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = References)
	FVector OriginalScale;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupMeshReference(USkeletalMeshComponent* NewMesh);

	void SetCMCReference(UCharacterMovementComponent* NewCMC) {
		CMC_Reference = NewCMC;
	}

};
