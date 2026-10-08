// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_SetAnimation.h"

#include "PaperFlipbookComponent.h"
#include "StateTreeExecutionContext.h"
#include "HordeShooter/Entities/Enemies/BaseEnemy.h"


EStateTreeRunStatus FSetAnimationTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FSetAnimationInstanceData& InstanceData = Context.GetInstanceData(*this);
	
	//UE_LOG(LogTemp, Warning, TEXT("EnterState animation change"));
	
	InstanceData.Enemy->PlayAnimation(InstanceData.Animation);
	
	return EStateTreeRunStatus::Succeeded;
}
