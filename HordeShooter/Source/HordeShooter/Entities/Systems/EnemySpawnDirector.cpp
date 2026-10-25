// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnDirector.h"

#include "GameFramework/Character.h"
#include "HordeShooter/Entities/DataAssets/EnemySpawnCard.h"
#include "HordeShooter/Runtime/EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawnDirector::AEnemySpawnDirector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawnDirector::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentCredits = StartingCredits;
	
	if (!DefaultTarget)
		DefaultTarget = Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	TrySpawnEnemies();
	
	GetWorld()->GetTimerManager().SetTimer(CreditTimerHandle, this, &AEnemySpawnDirector::IncreaseCredits, CreditIncreaseInterval, true);
}

void AEnemySpawnDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawnDirector::TrySpawnEnemies()
{
	if (Spawners.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No spawners active!"))
		return;
	}
	
	if (CurrentPresentEnemyCount >= MaxPresentEnemies)
	{
		UE_LOG(LogTemp,Warning, TEXT("Max present enemies exceeded!"))
		return;
	}
	
	TArray<UEnemySpawnCard*> SpawnCardCandidates;
	
	for (UEnemySpawnCard* SpawnCard : EnemySpawnCards)
	{
		if (CurrentCredits < SpawnCard->CreditCost)
			continue;
		
		SpawnCardCandidates.Add(SpawnCard);
	}
	
	if (SpawnCardCandidates.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No affordable enemy card found!"))
		
		float ActualInterval = FMath::RandRange(MinSpawnInterval, MaxSpawnInterval);
		
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawnDirector::TrySpawnEnemies, ActualInterval, false);
		return;
	}
	
	int CardIndex = FMath::RandRange(0, SpawnCardCandidates.Num() - 1);
	
	UEnemySpawnCard* SpawnCard = SpawnCardCandidates[CardIndex];
	
	while (CurrentCredits > SpawnCard->CreditCost && CurrentPresentEnemyCount < MaxPresentEnemies)
	{
		CurrentCredits -= SpawnCard->CreditCost;
		
		int SpawnerIndex = FMath::RandRange(0, Spawners.Num() - 1);
		
		Spawners[SpawnerIndex]->SpawnEnemy(SpawnCard, DefaultTarget);
		
		CurrentPresentEnemyCount++;
	}
	
	float ActualInterval = FMath::RandRange(MinSpawnInterval, MaxSpawnInterval);
		
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawnDirector::TrySpawnEnemies, ActualInterval, false);
}

void AEnemySpawnDirector::IncreaseCredits()
{
	CurrentCredits += CreditIncrease;
	
	//UE_LOG(LogTemp, Warning, TEXT("Credits increased: %d!"), CurrentCredits);
}

