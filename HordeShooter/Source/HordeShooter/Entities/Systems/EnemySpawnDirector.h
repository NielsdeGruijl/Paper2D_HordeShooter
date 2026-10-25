// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnDirector.generated.h"

class UEnemySpawnCard;
class AEnemySpawner;

UCLASS()
class HORDESHOOTER_API AEnemySpawnDirector : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Budget")
	int StartingCredits = 10;
	
	// Amount of credits to increase by per interval
	UPROPERTY(EditAnywhere, Category = "Budget")
	int CreditIncrease = 1;
	
	// Duration between credit increases in seconds
	UPROPERTY(EditAnywhere, Category = "Budget")
	float CreditIncreaseInterval = 1;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int MaxPresentEnemies = 20;
	
	// Duration between enemy spawn attempts in seconds
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MinSpawnInterval = 5;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float MaxSpawnInterval = 10;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<UEnemySpawnCard*> EnemySpawnCards;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<AEnemySpawner*> Spawners;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TObjectPtr<APawn> DefaultTarget;
	
private:
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY()
	FTimerHandle CreditTimerHandle;
	
	int CurrentPresentEnemyCount = 0;
	
	int CurrentCredits = 0;
	
public:	
	AEnemySpawnDirector();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
private:
	void TrySpawnEnemies();
	
	void IncreaseCredits();

};
