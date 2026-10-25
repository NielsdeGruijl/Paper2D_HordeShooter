// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_GetCurrentTarget.h"

#include "StateTreeExecutionContext.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"


void FGetCurrentTarget::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);
	
	Tick(Context, 0);
}

void FGetCurrentTarget::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FStateTreeEvaluatorCommonBase::Tick(Context, DeltaTime);
	
	FGetCurrentTargetInstanceData& InstanceData = Context.GetInstanceData(*this);
	
	TObjectPtr<ABasePaperEnemy> Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);

	InstanceData.Target = Enemy->GetTarget();
	
	if (!InstanceData.Target)
	{
		UE_LOG(LogTemp,Warning,TEXT("TARGET IS NULL"));
	}
}
