// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CharacterInput.h"
#include "Actors/BaseAI.h"
#include "Actors/BaseWeapon.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Utility/TargetComponent.h"
#include "Utility/AbilityComponent.h"
#include "Utility/ParryComponent.h"
#include "Utility/ResourcesComponent.h"

#include "Both/PlayerHUD.h"
#include "Both/CigaretteScreen.h"
#include "Both/CharacterAnimation.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "NavigationSystem.h" 

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../Cig_Fein.h"


// Sets default values
ACharacterInput::ACharacterInput()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	SpringArmComponent->SetRelativeRotation(FRotator(-45.f, -45.f, 0.f));
	SpringArmComponent->TargetArmLength = 1250.f;
	SpringArmComponent->SocketOffset = FVector(0.f, 0.f, 0.f);
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;

	WeaponChildActorRightComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponChildRightActor");
	WeaponChildActorRightComponent->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	WeaponChildActorLeftComponent = CreateDefaultSubobject<UChildActorComponent>("WeaponChildLeftActor");
	WeaponChildActorLeftComponent->SetupAttachment(GetMesh(), TEXT("hand_lSocket"));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmComponent);
	Camera->bUsePawnControlRotation = false;
	Camera->ProjectionMode = ECameraProjectionMode::Perspective;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	ParryComponent = CreateDefaultSubobject<UParryComponent>("ParryComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 1440.f, 0.f);

}

void ACharacterInput::Look(const FInputActionValue& Value)
{
	if (EInputActionValueType::Axis2D == Value.GetValueType())
	{
		CachedLookInput = Value.Get<FVector2D>();

	}
}

void ACharacterInput::AbilityAction(const FInputActionValue& Value)
{
	//print key value 
	float PressedKey = Value.Get<float>();

	if (!AbilityComponent) return;
	if (!TargetComponent) return;

	if(AbilityComponent->CheckIfAbilityOnCooldown(static_cast<int32>(PressedKey)))
		return;

	if (AActor* target = TargetComponent->GetTargetActor())
	{
		AbilityComponent->SetCastLocation(LeftWeaponObject->GetMuzzleLocation());
		AbilityComponent->OnAbilityUsed.Broadcast(static_cast<int32>(PressedKey), target);
	}
}

void ACharacterInput::ParryAction()
{
	if (!ParryComponent) return;
	
	ParryComponent->StartParry();
}

void ACharacterInput::ClickRightMouse()
{
	FHitResult HitResult = GetResultUnderCursor();

	if (HitResult.bBlockingHit)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, HitResult.Location);
	}


}

void ACharacterInput::ClickLeftMouse()
{
	if (!TargetComponent) return;
	FHitResult HitResult = GetResultUnderCursor();

	if (HitResult.bBlockingHit)
	{
		if (AActor* ai = HitResult.GetActor())
		{
			if (ai->Implements<UTargetInterface>())
			{
				ITargetInterface* targetInterface = Cast<ITargetInterface>(ai);
				if (targetInterface)
				{
					targetInterface->SetTargetedColorState();
					TargetComponent->SetTargetingActor(ai);
				}
				else
				{
					UE_LOG(Game, Log, TEXT("Targeted Actor does not implement Target Interface"));
				}
			}
			else
			{
				if(TargetComponent->GetTargetActor())
				{
					TargetComponent->ClearTargetActor();
				}
			}
		}

		
	}


}

// Called when the game starts or when spawned
void ACharacterInput::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{

			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}

		PlayerController->bShowMouseCursor = true;

		UUserWidget* hud = CreateWidget(PlayerController, HUDClass);


		PlayerHud = Cast<UPlayerHUD>(hud);
		
		if (PlayerHud)
		{
			PlayerHud->AddToViewport();
		}
	}

	CharacterAnimInst = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());

	WeaponChildActorLeftComponent->SetChildActorClass(HandCannonClass);
	WeaponChildActorLeftComponent->CreateChildActor();
	LeftWeaponObject = Cast<ABaseWeapon>(WeaponChildActorLeftComponent->GetChildActor());

	WeaponChildActorRightComponent->SetChildActorClass(SwordClass);
	WeaponChildActorRightComponent->CreateChildActor();
	RightWeaponObject = Cast<ABaseWeapon>(WeaponChildActorRightComponent->GetChildActor());

	if(AbilityComponent)
	{
		if (LeftWeaponObject && RightWeaponObject)
		{
			LeftWeaponObject->SetOwner(this);
			RightWeaponObject->SetOwner(this);
		}

		if (CharacterAnimInst)
		{
			AbilityComponent->SetAnimationRef(CharacterAnimInst);
			CharacterAnimInst->OnAbilityUsed.AddDynamic(CharacterAnimInst, &UCharacterAnimation::UseAbilityAnimation);
		}

		if(ResourceComponent)
		{
			AbilityComponent->SetResourceRef(ResourceComponent);
		}
	}


	if (ParryComponent)
	{
		if (CharacterAnimInst)
		{
			ParryComponent->SetAnimationRef(CharacterAnimInst);
			CharacterAnimInst->OnParryUsed.AddDynamic(CharacterAnimInst, &UCharacterAnimation::UseParryAnimation);
		}
	}

	if(ResourceComponent && PlayerHud)
	{
		ResourceComponent->OnHealthChangeHUD.AddDynamic(PlayerHud, &UPlayerHUD::SetHealthBarPercent);
		ResourceComponent->OnSpiritChangeHUD.AddDynamic(PlayerHud, &UPlayerHUD::SetSpiritBarPercent);
	}
}

// Called every frame
void ACharacterInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterInput::Look);
		EnhancedInputComp->BindAction(AbilitySlotActions, ETriggerEvent::Started, this, &ACharacterInput::AbilityAction);
		EnhancedInputComp->BindAction(ParrySlotAction, ETriggerEvent::Started, this, &ACharacterInput::ParryAction);
		EnhancedInputComp->BindAction(RClickAction, ETriggerEvent::Triggered, this, &ACharacterInput::ClickRightMouse);
		EnhancedInputComp->BindAction(LClickAction, ETriggerEvent::Started, this, &ACharacterInput::ClickLeftMouse);
		
	}

}

float ACharacterInput::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!ResourceComponent) return 0.f;

	ResourceComponent->OnHealthChange.Broadcast(DamageAmount);

	return 0.f;
}


void ACharacterInput::StopAllMovement()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, GetActorLocation());
}

void ACharacterInput::SetTargetedColorState()
{
	Super::SetTargetedColorState();

}

void ACharacterInput::SetTargetedActor(AActor* NewTarget)
{
	Super::SetTargetedActor(NewTarget);
}

void ACharacterInput::HandleHurt(float unusedAmount)
{
	Super::HandleHurt(unusedAmount);

	//animation later used
}


FHitResult ACharacterInput::GetResultUnderCursor()
{
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	return HitResult;
}

