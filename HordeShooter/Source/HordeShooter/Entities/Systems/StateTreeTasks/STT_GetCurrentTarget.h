// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "STT_GetCurrentTarget.generated.h"

/**
 * 
 */
USTRUCT()
struct FGetCurrentTargetInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<APawn> Target;
};

USTRUCT()
struct HORDESHOOTER_API FGetCurrentTarget : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FGetCurrentTargetInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
	
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};
