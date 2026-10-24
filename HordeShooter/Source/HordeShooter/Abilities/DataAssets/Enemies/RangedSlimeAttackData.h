// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyAbilityData.h"
#include "RangedSlimeAttackData.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API URangedSlimeAttackData : public UBaseEnemyAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere)
	float ProjectileArc;
};
