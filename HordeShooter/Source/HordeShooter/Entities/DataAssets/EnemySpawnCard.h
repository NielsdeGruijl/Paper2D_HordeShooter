// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemySpawnCard.generated.h"

class ABasePaperEnemy;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UEnemySpawnCard : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasePaperEnemy> EnemyClass;
	
	UPROPERTY(EditAnywhere)
	float ZOffset;
	
	UPROPERTY(EditAnywhere)
	int CreditCost;
};
