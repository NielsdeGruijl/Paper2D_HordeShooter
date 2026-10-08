// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthManager.h"

#include "GameFramework/Actor.h"

UHealthManager::UHealthManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthManager::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
}

void UHealthManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthManager::TakeDamage(float DamageAmount)
{
	CurrentHealth =	FMath::Max(0, CurrentHealth - DamageAmount);

	OnHealthChanged.Broadcast(CurrentHealth);
	
	if (CurrentHealth <= 0)
	{
		GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this,
			&UHealthManager::DelayedDestruction, DestructionTime);
		
	}
}

void UHealthManager::DelayedDestruction()
{
	GetOwner()->Destroy();
}

