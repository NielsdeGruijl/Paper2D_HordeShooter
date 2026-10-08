// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "Conditions/StateTreeAIConditionBase.h"

#include "Tasks/StateTreeAITask.h"

#include "EnemyStateTreeUtility.generated.h"

class ABaseEnemy;
class UHealthManager;
class ACharacter;
class APawn;

/**
 * 
 */

USTRUCT()
struct HORDESHOOTER_API FAIContext
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<UHealthManager> HealthManager;
};


// ======================= Get Current Health Evaluator ===========================

USTRUCT()
struct HORDESHOOTER_API FGetCurrentHealthEvaluatorInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float Health;
};

USTRUCT()
struct HORDESHOOTER_API FGetCurrentHealth : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FGetCurrentHealthEvaluatorInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	
};


// ====================== Get Player Task ==============================

USTRUCT()
struct HORDESHOOTER_API FGetPlayerTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	TObjectPtr<ACharacter> TargetPlayer;
};

USTRUCT()
struct HORDESHOOTER_API FGetPlayerTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FGetPlayerTaskInstanceData;
	virtual const UStruct* GetInstanceDataType() const override 
	{ return FInstanceDataType::StaticStruct(); }
	
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	
};