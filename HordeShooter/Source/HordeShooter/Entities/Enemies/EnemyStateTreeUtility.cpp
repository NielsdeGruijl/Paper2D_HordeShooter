// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyStateTreeUtility.h"

#include "BaseEnemy.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeExecutionTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"

//

void FGetCurrentHealth::TreeStart(FStateTreeExecutionContext& Context) const
{
	FStateTreeEvaluatorCommonBase::TreeStart(Context);
	
	Tick(Context, 0);
}

void FGetCurrentHealth::Tick(FStateTreeExecutionContext& Context, 
	const float DeltaTime) const
{
	FGetCurrentHealthEvaluatorInstanceData& InstanceData = 
		Context.GetInstanceData(*this);
	
	if (!InstanceData.Pawn)
	{
		UE_LOG(LogTemp, Error, TEXT("NO CHARACTER"));
		
		InstanceData.Health = 0;
		return;
	}
	
	UHealthManager* HealthManager = InstanceData.Pawn->FindComponentByClass<UHealthManager>();
	
	if (!HealthManager)
	{
		UE_LOG(LogTemp, Error, TEXT("NO HEALTH MANAGER"));
		
		InstanceData.Health = 0;
		return;
	}
	
	InstanceData.Health = HealthManager->CurrentHealth;
}

EStateTreeRunStatus FGetPlayerTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FGetPlayerTaskInstanceData& InstanceData = Context.GetInstanceData(*this);
	
	InstanceData.TargetPlayer = 
		Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0));

	return EStateTreeRunStatus::Running;
}
