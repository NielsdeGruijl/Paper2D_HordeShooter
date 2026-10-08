// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tasks/StateTreeAITask.h"
#include "STT_PerformAttack.generated.h"

/**
 * 
 */

class ABaseEnemy;

USTRUCT()
struct HORDESHOOTER_API FPerformAttackInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
};

USTRUCT()
struct HORDESHOOTER_API FPerformAttack : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	
	
	using FInstanceDataType = FPerformAttackInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
