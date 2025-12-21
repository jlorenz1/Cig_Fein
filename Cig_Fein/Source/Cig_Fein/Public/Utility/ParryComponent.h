// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnParrySuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParry, bool, bStart);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CIG_FEIN_API UParryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnParrySuccess OnParrySuccess;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnParry OnParry;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parry")
	class UAnimMontage* ParryAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parry")
	TSubclassOf<UCameraShakeBase> ParryCameraShake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	class UCharacterAnimation* AnimationRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parry")
	AActor* OwnerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Parry")
	AActor* ClosestParryActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Parry")
	AActor* ParryingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float CheckRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float ParryCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float ParryRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	bool bCanParry = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	bool bParryHappening = false;

	

	UFUNCTION()
	void ParryClosestActor();

	void ResetParry();

	FTimerHandle ParryTimer;

	UFUNCTION()
	void SetParryBoxCollisions(bool bStart);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	void StartParry();

	void SetAnimationRef(UCharacterAnimation* NewAnimationRef) {
		AnimationRef = NewAnimationRef;
	}

	void onParryStart(FVector SocketLocation);

	void onParryEnd();

	bool CanParry();
private:

	AActor* GetClosestParrableActor();

	void SlowWorldOnParry();

	
};
