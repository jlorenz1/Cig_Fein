// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterInput.generated.h"

UCLASS()
class CIG_FEIN_API ACharacterInput : public AABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterInput();

	void Look(const FInputActionValue& Value);
	void AbilityAction(const FInputActionValue& Value);
	void ParryAction();
	void ClickLeftMouse();
	void ClickRightMouse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* RClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* AbilitySlotActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ParrySlotAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	class UParryComponent* ParryComponent;

	UPROPERTY(VisibleAnywhere, Category = Weapons)
	class UChildActorComponent* WeaponChildActorLeftComponent;

	UPROPERTY(VisibleAnywhere, Category = Weapons)
	class UChildActorComponent* WeaponChildActorRightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapons)
	class ABaseWeapon* LeftWeaponObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapons)
	class ABaseWeapon* RightWeaponObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	TSubclassOf<AActor> HandCannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	TSubclassOf<AActor> SwordClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	class UPlayerHUD* PlayerHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	class UCigaretteScreen* CigTestScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<UUserWidget> HUDClass;

	FVector2D CachedMoveInput;
	FVector2D CachedLookInput;

	bool inAction = false;

	virtual void HandleHurt(float unusedAmount) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	void StopAllMovement();

	//INTERFACE IMPLEMENTATION
	virtual void SetTargetedColorState() override;
	virtual void SetTargetedActor(AActor* NewTarget) override;

private:

	FHitResult GetResultUnderCursor();
};
