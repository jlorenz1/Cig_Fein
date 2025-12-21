// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CIG_FEIN_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	AActor* TargetActor;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	class UMaterialInstanceDynamic* OutlineMID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ColorStates")
	FLinearColor UnTargetedColorState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ColorStates")
	FLinearColor TargetedColorState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targeting")
	bool bIsTargeted = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetTargeted();

	void ClearTargetActor();

	void SetTargetingActor(AActor* NewTarget);

	AActor* GetTargetActor() {
		return TargetActor;
	}

	 void SetColorState(FLinearColor ColorState);

};
