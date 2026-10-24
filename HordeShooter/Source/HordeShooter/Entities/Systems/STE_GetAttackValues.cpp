// Fill out your copyright notice in the Description page of Project Settings.


#include "STE_GetAttackValues.h"

#include "StateTreeExecutionContext.h"
#include "HordeShooter/EnemyWeaponController.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"


void FGetAttackPlan::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);
	
	FGetAttackPlanInstanceData& InstanceData =
		Context.GetInstanceData(*this);
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);
	
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Context pawn is not enemy"))
		return;
	}
	
	Tick(Context, 0);
}

void FGetAttackPlan::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FStateTreeEvaluatorCommonBase::Tick(Context, DeltaTime);
	
	FGetAttackPlanInstanceData& InstanceData =
		Context.GetInstanceData(*this);
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);
	
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Context pawn is not enemy"))
		return;
	}
	
	if (!Enemy->GetWeapon())
	{
		UE_LOG(LogTemp, Warning, TEXT("Context pawn weapon not initialized"))
		return;
	}
	
	const FPlanOfAttack* Plan = &Enemy->GetWeapon()->CurrentPlan;
	
	InstanceData.Plan = *Plan;
	
	InstanceData.bNeedsNewPlan = Plan->CreationTime + Plan->ReevaluationTime <= InstanceData.Pawn->GetWorld()->GetTimeSeconds();
}