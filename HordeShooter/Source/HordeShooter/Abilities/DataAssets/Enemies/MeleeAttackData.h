// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyAbilityData.h"
#include "MeleeAttackData.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UMeleeAttackData : public UBaseEnemyAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FVector MeleeHitboxBounds;
};
