// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "STE_GetAttackValues.generated.h"


USTRUCT()
struct HORDESHOOTER_API FGetAttackValuesInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float MinimumChaseDistance = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float StopChaseDistance = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float MinimumAttackDistance = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float AttackCooldown = 0;
};

USTRUCT()
struct HORDESHOOTER_API FGetAttackValues : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FGetAttackValuesInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};