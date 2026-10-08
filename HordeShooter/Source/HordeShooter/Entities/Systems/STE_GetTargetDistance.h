// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"

#include "STE_GetTargetDistance.generated.h"

/**
 * 
 */

class ABaseEnemy;

USTRUCT()
struct HORDESHOOTER_API FGetDistanceToTargetInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float Distance;
};

USTRUCT()
struct HORDESHOOTER_API FGetDistanceToTarget : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FGetDistanceToTargetInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};