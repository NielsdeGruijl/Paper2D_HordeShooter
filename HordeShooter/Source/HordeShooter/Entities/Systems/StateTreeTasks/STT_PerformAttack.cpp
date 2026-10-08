// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_PerformAttack.h"

#include "StateTreeExecutionContext.h"
#include "GameFramework/Character.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"
#include "Kismet/GameplayStatics.h"

EStateTreeRunStatus FPerformAttack::EnterState(FStateTreeExecutionContext& Context,
                                               const FStateTreeTransitionResult& Transition) const
{
	FPerformAttackInstanceData& InstanceData = Context.GetInstanceData(*this);
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);
	
	ACharacter* Player = 
		Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0));
	
	if (!Enemy)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	Enemy->Attack(Player);
	
	return EStateTreeRunStatus::Succeeded;
}
