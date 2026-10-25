// Fill out your copyright notice in the Description page of Project Settings.


#include "STE_GetTargetDistance.h"

#include "StateTreeExecutionContext.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"

void FGetDistanceToTarget::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);
	
	Tick(Context, 0);
}

void FGetDistanceToTarget::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FStateTreeEvaluatorCommonBase::Tick(Context, DeltaTime);
	

	
	FGetDistanceToTargetInstanceData& InstanceData =
		Context.GetInstanceData(*this);
	
	TObjectPtr<APawn> Target = InstanceData.Pawn->GetTarget();
	
	if (!Target)
	{
		//UE_LOG(LogTemp, Error, TEXT("Target is nullptr"));
		
		InstanceData.Distance = 0;
		return;
	}
	
	FVector Diff = Target->GetActorLocation() - InstanceData.Pawn->GetActorLocation();
	
	InstanceData.Distance = Diff.Length();
	
	//UE_LOG(LogTemp,Warning,TEXT("Distance to target: %f"), InstanceData.Distance);
}
