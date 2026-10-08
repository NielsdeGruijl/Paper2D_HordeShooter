// Fill out your copyright notice in the Description page of Project Settings.


#include "STE_GetTargetDistance.h"

#include "StateTreeExecutionContext.h"
#include "GameFramework/Character.h"
#include "HordeShooter/Entities/Enemies/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"


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
	
	ACharacter* Player = 
		Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0));
	
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is nullptr"));
		
		InstanceData.Distance = 0;
		return;
	}
	
	FVector Diff = Player->GetActorLocation() - InstanceData.Pawn->GetActorLocation();
	
	InstanceData.Distance = Diff.Length();
	
	//UE_LOG(LogTemp,Warning,TEXT("Distance to target: %f"), InstanceData.Distance);
}
