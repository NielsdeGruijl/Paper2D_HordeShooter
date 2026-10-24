// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyAbility.h"
#include "RangedSlimeAttack.generated.h"

class URangedSlimeAttackData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API URangedSlimeAttack : public UBaseEnemyAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	URangedSlimeAttackData* AbilityData;
	
public:
	virtual void StartInternal(FVector OriginPosition, FVector TargetPosition) override;
	
	virtual void Stop() override;
	
protected:
	virtual void Initialize(UBaseAbilityData* pAbilityData) override;
};
