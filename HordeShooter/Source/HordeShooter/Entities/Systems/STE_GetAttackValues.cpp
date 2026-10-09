// Fill out your copyright notice in the Description page of Project Settings.


#include "STE_GetAttackValues.h"

#include "StateTreeExecutionContext.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"


void FGetAttackValues::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);
	
	Tick(Context, 0);
}

void FGetAttackValues::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FStateTreeEvaluatorCommonBase::Tick(Context, DeltaTime);
	
	FGetAttackValuesInstanceData& InstanceData =
		Context.GetInstanceData(*this);
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);
	
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Context pawn is not enemy"))
		return;
	}
	
	InstanceData.MinimumChaseDistance = Enemy->MinimumChaseDistance;
	InstanceData.MinimumAttackDistance = Enemy->MinimumAttackDistance;
	InstanceData.StopChaseDistance = InstanceData.MinimumAttackDistance - 50;
	InstanceData.AttackCooldown = Enemy->AttackCooldown;
}
