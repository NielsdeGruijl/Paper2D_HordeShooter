// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "HordeShooter/EnemyWeaponController.h"
#include "STE_GetAttackValues.generated.h"

USTRUCT()
struct HORDESHOOTER_API FGetAttackPlanInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	FPlanOfAttack Plan;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	bool bNeedsNewPlan = false;
};

USTRUCT()
struct HORDESHOOTER_API FGetAttackPlan : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FGetAttackPlanInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};