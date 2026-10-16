// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class UEnemySpawnCard;

UCLASS()
class HORDESHOOTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	
public:	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	void SpawnEnemy(UEnemySpawnCard* SpawnCard);
	
private:
};
