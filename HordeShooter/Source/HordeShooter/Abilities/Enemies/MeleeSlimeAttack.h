// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyAbility.h"
#include "MeleeSlimeAttack.generated.h"

class UMeleeAttackData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UMeleeSlimeAttack : public UBaseEnemyAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UMeleeAttackData* AbilityData;
	
public:
	virtual void StartInternal(FVector OriginPosition, FVector TargetPosition) override;
	
	virtual void Stop() override;
	
protected:
	virtual void Initialize(UBaseAbilityData* pAbilityData) override;
};
