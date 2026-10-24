// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWeaponController.h"

#include <string>

#include "Abilities/Enemies/BaseEnemyAbility.h"
#include "Entities/Enemies/BasePaperEnemy.h"
#include "Kismet/GameplayStatics.h"

void UEnemyWeaponController::Initialize(UWeaponData* WeaponToSet)
{
	Super::Initialize(WeaponToSet);
	
	for (UBaseWeaponAbility* Ability : Abilities)
	{
		if (UBaseEnemyAbility* EnemyAbility = Cast<UBaseEnemyAbility>(Ability))
			EnemyAbilities.Add(EnemyAbility);
	}
	
	if (ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(OwningPawn))
		Owner = Enemy;
	
	CurrentPlan = FPlanOfAttack();
}

void UEnemyWeaponController::StartAbility(int32 AbilityIndex, FVector OriginLocation, FVector TargetLocation)
{
	Super::StartAbility(AbilityIndex, OriginLocation, TargetLocation);
	
	CurrentPlan.bIsValid = false;
	
	CurrentPlan.bIsExecuting = false;
	
	/*FString string = FString::SanitizeFloat((TargetLocation - OriginLocation).Length());
	DrawDebugString(GetWorld(), OwningPawn->GetActorLocation() + FVector::ZAxisVector * 200, string);*/
}

void UEnemyWeaponController::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
	
	DrawDebugSphere(GetWorld(), OwningPawn->GetActorLocation(), CurrentPlan.MinimumRange, 24, FColor::Green, false, 0);
	DrawDebugSphere(GetWorld(), OwningPawn->GetActorLocation(), CurrentPlan.MaximumRange, 24, FColor::Red, false, 0);
	
	FString string = FString::SanitizeFloat(CurrentPlan.bIsValid);
	string = FString("Is plan valid: ") + string;
	DrawDebugString(GetWorld(), OwningPawn->GetActorLocation() + FVector::ZAxisVector * 200, string, nullptr, FColor::White, 0);
	
	FString string2 = FString::SanitizeFloat(CurrentPlan.bIsExecuting);
	string2 = FString("Is plan Executing: ") + string2;
	DrawDebugString(GetWorld(), OwningPawn->GetActorLocation() + FVector::ZAxisVector * 150, string2, nullptr, FColor::White, 0);
}

bool UEnemyWeaponController::FormulatePlan(const APawn& Target)
{
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not formulate plan, Owner is nullptr"));
		return false;
	}
	
	float BestScore = 0;
	int32 BestAbilityIndex = 0;
	
	for (int32 i = 0; i < EnemyAbilities.Num(); i++)
	{
		if (EnemyAbilities[i]->GetOnCooldown())
			continue;
		
		float Score = EnemyAbilities[i]->Evaluate(*Owner, Target);
		
		if (Score > BestScore)
		{
			BestScore = Score;
			BestAbilityIndex = i;
		}
	}
	
	if (BestScore == 0)
	{
		CurrentPlan.bIsValid = false;
		return false;
	}
	
	CurrentPlan.AttackAbilityIndex = BestAbilityIndex;
	CurrentPlan.MinimumRange = EnemyAbilities[BestAbilityIndex]->GetMinimumAttackRange();
	CurrentPlan.MaximumRange = EnemyAbilities[BestAbilityIndex]->GetMaximumAttackRange();
	
	CurrentPlan.StopChasingRange = CurrentPlan.MinimumRange;
	
	CurrentPlan.CreationTime = GetWorld()->GetTimeSeconds();
	
	CurrentPlan.bIsValid = true;
	
	return true;
}
