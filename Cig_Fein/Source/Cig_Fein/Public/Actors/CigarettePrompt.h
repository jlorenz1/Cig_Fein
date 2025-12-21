// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CigarettePrompt.generated.h"

UCLASS()
class CIG_FEIN_API ACigarettePrompt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACigarettePrompt();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* TriggerBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCigaretteScreen* CigaretteScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CigaretteScreenClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void BoundOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
