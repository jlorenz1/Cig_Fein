// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class CIG_FEIN_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	AActor* FiringActor;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float LifeSpan = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bCanParry = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
	float bDistanceToTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	AActor* Target;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetHomingTarget(AActor* TargetActor);

	virtual void SetFiringActor(AActor* Actor) {
		FiringActor = Actor;
	};
};
