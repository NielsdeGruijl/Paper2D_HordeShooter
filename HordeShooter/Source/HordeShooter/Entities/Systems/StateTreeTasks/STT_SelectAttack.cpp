// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_SelectAttack.h"

#include "StateTreeExecutionContext.h"
#include "GameFramework/Character.h"
#include "HordeShooter/EnemyWeaponController.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"
#include "Kismet/GameplayStatics.h"

EStateTreeRunStatus FSelectAttack::EnterState(FStateTreeExecutionContext& Context,
                                              const FStateTreeTransitionResult& Transition) const
{
	FSelectAttackInstanceData& InstanceData = Context.GetInstanceData(*this);
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(InstanceData.Pawn);
	
	ACharacter* Player = 
		Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0));
	
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy pawn is nullptr"));
		return EStateTreeRunStatus::Failed;
	}
	
	if (!Enemy->GetWeapon())
	{
		UE_LOG(LogTemp, Warning, TEXT("Context pawn weapon is not initialized"));
		return EStateTreeRunStatus::Failed;
	}
	
	bool bSuccessfullyFormulatedPlan = Enemy->GetWeapon()->FormulatePlan(*Player);
	
	if (!bSuccessfullyFormulatedPlan)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to formulate plan"));
		return EStateTreeRunStatus::Failed;
	}
	
	InstanceData.SelectedPlan = Enemy->GetWeapon()->CurrentPlan;
	
	UE_LOG(LogTemp, Warning, TEXT("Selected new attack plan: \n Ability Index: %d \n StopChasing Distance: %f \n Maximum Attack Range: %f \n!"), 
		InstanceData.SelectedPlan.AttackAbilityIndex,
		InstanceData.SelectedPlan.StopChasingRange,
		InstanceData.SelectedPlan.MaximumRange);
	
	return EStateTreeRunStatus::Succeeded;
}
