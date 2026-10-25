// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_PerformAttack.h"

#include "StateTreeExecutionContext.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"

EStateTreeRunStatus FPerformAttack::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FPerformAttackInstanceData& InstanceData = Context.GetInstanceData(*this);
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);
	
	Enemy->Attack(InstanceData.AttackAbilityIndex);
	
	return EStateTreeRunStatus::Succeeded;
}