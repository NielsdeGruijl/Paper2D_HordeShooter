// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeaponAbility.h"
#include "BaseEnemyAbility.generated.h"

class ABasePaperEnemy;
class UBaseEnemyAbilityData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UBaseEnemyAbility : public UBaseWeaponAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UBaseEnemyAbilityData* BaseAbilityData;
	
public:
	virtual void Initialize(UBaseAbilityData* pAbilityData);
	
	virtual float Evaluate(const ABasePaperEnemy& Enemy, const APawn& Target);
	
	TTuple<float, float> GetAttackRange();
	
	float GetMinimumAttackRange() const;
	
	float GetMaximumAttackRange() const;
};
