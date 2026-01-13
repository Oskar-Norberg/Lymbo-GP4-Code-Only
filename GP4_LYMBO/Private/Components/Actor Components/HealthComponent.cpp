// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actor Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComponent::TakeDamage(float Damage, UDamageType* DamageType, AController* WhoDamagedMe, AActor* WhatDamagedMe)
{
	if (CanTakeDamage)
	{
		if (Health - Damage <= 0)
		{
			Health = 0;
			Death();
		}
		else
		{
			Health -= Damage;
		}

		OnHealthChanged.Broadcast();
		OnTakenDamage.Broadcast();
	}
	
	CanTakeDamage = false;
	GetWorld()->GetTimerManager().SetTimer(IFrameTimerHandle, this, &UHealthComponent::EnableDamage, IFramesDuration, false);
}

void UHealthComponent::RecoverHealth(float Healing)
{
	if (CanRecoverHealth)
	{
		if (Health + Healing <= MaxHealth)
		{
			Health = MaxHealth;
		}
		else
		{
			Health = Health + Healing;
		}

		OnHealthChanged.Broadcast();
		OnRecoveredHealth.Broadcast();
	}
}

void UHealthComponent::EnableDamage()
{
	CanTakeDamage = true;
}

void UHealthComponent::Death()
{
	OnDeath.Broadcast();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

