// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/ResourcesComponent.h"

#include "../Cig_Fein.h"

// Sets default values for this component's properties
UResourcesComponent::UResourcesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UResourcesComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentSpirit = MaxSpirit;

	OnHealthChange.AddDynamic(this, &UResourcesComponent::SetHealth);
	OnSpiritChange.AddDynamic(this, &UResourcesComponent::SetSpirit);
	// ...
	
}


// Called every frame
void UResourcesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentHealth < MaxHealth)
	{
		float HregenAmount = HealthRegenRate * DeltaTime;
		OnHealthChange.Broadcast(-HregenAmount);
	}

	if(CurrentSpirit < MaxSpirit)
	{
		float SregenAmount = SpiritRegenRate * DeltaTime;
		OnSpiritChange.Broadcast(-SregenAmount);
	}

	if(CurrentHealth >= MaxHealth && CurrentSpirit >= MaxSpirit)
	{
		SetComponentTickEnabled(false);
	}
	// ...
}

void UResourcesComponent::SetHealth(float NewHealth)
{
	float newAmount = CurrentHealth - NewHealth;
	
	CurrentHealth = FMath::Clamp(newAmount, 0.f, MaxHealth);

	if(CurrentHealth <= 0.f)
	{
		// Handle Death
		UE_LOG(Game, Log, TEXT("Death: %f"), CurrentHealth);
	}

	OnHealthChangeHUD.Broadcast(CurrentHealth / MaxHealth);

	if(CurrentHealth < MaxHealth && bCanRegenResources)
	{
		SetComponentTickEnabled(true);
	}

}

void UResourcesComponent::SetSpirit(float NewSpirit)
{
	float newAmount = CurrentSpirit - NewSpirit;

	CurrentSpirit = FMath::Clamp(newAmount, 0.f, MaxSpirit);

	if(CurrentSpirit <= 0.f)
	{
		// Handle Out of Spirit
		UE_LOG(Game, Log, TEXT("Out of Spirit: %f"), CurrentSpirit);
	}

	OnSpiritChangeHUD.Broadcast(CurrentSpirit / MaxSpirit);

	if(CurrentSpirit < MaxSpirit && bCanRegenResources)
	{
		SetComponentTickEnabled(true);
	}
}

