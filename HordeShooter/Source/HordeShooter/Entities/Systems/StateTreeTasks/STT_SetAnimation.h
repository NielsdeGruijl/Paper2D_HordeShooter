// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "HordeShooter/Entities/Enemies/BaseEnemy.h"
#include "Tasks/StateTreeAITask.h"
#include "STT_SetAnimation.generated.h"

/**
 * 
 */

class ABaseEnemy;
class UPaperFlipbook;

USTRUCT()
struct HORDESHOOTER_API FSetAnimationInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = "Context")
	ABaseEnemy* Enemy;
	
	UPROPERTY(EditAnywhere)
	EEnemyAnimation Animation;
	
};


USTRUCT()
struct HORDESHOOTER_API FSetAnimationTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FSetAnimationInstanceData;
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
