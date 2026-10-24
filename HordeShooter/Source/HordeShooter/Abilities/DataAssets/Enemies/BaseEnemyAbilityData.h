// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseAbilityData.h"
#include "BaseEnemyAbilityData.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UBaseEnemyAbilityData : public UBaseAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Chase values")
	float MinimumAttackRange = 0;
	
	UPROPERTY(EditAnywhere, Category = "Chase values")
	float MaximumAttackRange = 0;
};
