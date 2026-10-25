// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "SlimeGrowthProjectile.generated.h"

class UEnemySpawnCard;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API ASlimeGrowthProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "EnemySpawning")
	TArray<UEnemySpawnCard*> EnemyTypesToSpawn;
	
	UPROPERTY(EditAnywhere, Category = "EnemySpawning")
	int EnemySpawnCredits = 5;
	
	UPROPERTY(EditAnywhere, Category = "EnemySpawning")
	int MaxEnemiesToSpawn = 3;
	
private:
	float ImpactSphereRadius = 500;
	
public:
	virtual void Initialize(float Damage, float ImpactRadius);
	
protected:
	virtual void OnOverlapInternal(AActor* OtherActor) override;
	
private:
	void SpawnEnemy(UEnemySpawnCard* Card);
};
