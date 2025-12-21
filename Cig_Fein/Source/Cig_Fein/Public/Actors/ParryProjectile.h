// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "ParryProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CIG_FEIN_API AParryProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:

	AParryProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetHomingTarget(AActor* TargetActor);
	
	void GetParried(AActor* NewOwner);

	float GetWindowTimeLeft() {
		return bWindowTimeLeft;
	}

	bool IsInParryWindow(FVector ParryingActorLocation) {
		bDistanceToTarget = FVector::Dist(GetActorLocation(), ParryingActorLocation);
		return (bDistanceToTarget <= bParryWindowDistanceMax && bDistanceToTarget >= bParryWindowDistanceMin);
	}


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int32 HitReacts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	float bWindowTimeLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	float bHasParryComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float bParryWindowDistanceMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float bParryWindowDistanceMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ParryDamageDamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ParryDamageMultiplier;
};
