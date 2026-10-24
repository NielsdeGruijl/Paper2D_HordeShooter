// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAbility.h"

#include "HordeShooter/Abilities/DataAssets/Enemies/BaseEnemyAbilityData.h"


void UBaseEnemyAbility::Initialize(UBaseAbilityData* pAbilityData)
{
	Super::Initialize(pAbilityData);
	
	BaseAbilityData = Cast<UBaseEnemyAbilityData>(pAbilityData);
}

float UBaseEnemyAbility::Evaluate(const ABasePaperEnemy& Enemy, const APawn& Player)
{
	return 1.0f;
}

TTuple<float, float> UBaseEnemyAbility::GetAttackRange()
{
	return TTuple<float, float>(BaseAbilityData->MinimumAttackRange, BaseAbilityData->MaximumAttackRange);
}

float UBaseEnemyAbility::GetMinimumAttackRange() const
{
	return BaseAbilityData->MinimumAttackRange;
}

float UBaseEnemyAbility::GetMaximumAttackRange() const
{
	return BaseAbilityData->MaximumAttackRange;
}
