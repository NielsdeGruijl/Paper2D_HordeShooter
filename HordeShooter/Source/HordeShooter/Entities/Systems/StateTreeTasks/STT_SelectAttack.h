// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HordeShooter/EnemyWeaponController.h"
#include "Tasks/StateTreeAITask.h"
#include "STT_SelectAttack.generated.h"

/**
 * 
 */

USTRUCT()
struct HORDESHOOTER_API FSelectAttackInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	FPlanOfAttack SelectedPlan;
};

USTRUCT()
struct HORDESHOOTER_API FSelectAttack : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FSelectAttackInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
