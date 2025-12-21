// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ABaseCharacter.h"

#include "Utility/ResourcesComponent.h"
#include "Utility/TargetComponent.h"
#include "Utility/AbilityComponent.h"

#include "Both/CharacterAnimation.h"	
#include "../Cig_Fein.h"

// Sets default values
AABaseCharacter::AABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
	ResourceComponent = CreateDefaultSubobject<UResourcesComponent>("ResourceComponent");
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>("AbilityComponent");

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));


}

// Called when the game starts or when spawned
void AABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Idle = FGameplayTag::RequestGameplayTag(FName("State.Idle"));
	Attacking = FGameplayTag::RequestGameplayTag(FName("State.Attacking"));
	Parrying = FGameplayTag::RequestGameplayTag(FName("State.Parrying"));
	Stunned = FGameplayTag::RequestGameplayTag(FName("State.Stunned"));
	Dead = FGameplayTag::RequestGameplayTag(FName("State.Dead"));

	CharacterAnimInst = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());

	if (ResourceComponent)
	{
		ResourceComponent->OnHealthChange.AddDynamic(this, &AABaseCharacter::HandleHurt);
	}
}

// Called every frame
void AABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!ResourceComponent) return 0.f;

	ResourceComponent->OnHealthChange.Broadcast(DamageAmount);

	return 0.f;
}

void AABaseCharacter::SetTargetedColorState()
{
	if (!TargetComponent) return;
	TargetComponent->SetTargeted();
}

void AABaseCharacter::SetTargetedActor(AActor* NewTarget)
{
	if (!TargetComponent) return;
	TargetComponent->SetTargetingActor(NewTarget);
}

void AABaseCharacter::HandleHurt(float unusedAmount)
{
	//animation later used
}





