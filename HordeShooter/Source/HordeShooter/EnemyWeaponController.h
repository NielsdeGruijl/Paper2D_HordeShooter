// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerWeaponController.h"
#include "EnemyWeaponController.generated.h"

/**
 * 
 */

class ABasePaperEnemy;
class UBaseEnemyAbility;

USTRUCT()
struct FPlanOfAttack
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<APawn> Target;
	
	UPROPERTY(EditAnywhere)
	int32 AttackAbilityIndex;
	
	UPROPERTY(EditAnywhere)
	float CreationTime;
	
	UPROPERTY(EditAnywhere)
	float ReevaluationTime = 10;
	
	UPROPERTY(EditAnywhere)
	float MinimumRange;
	
	UPROPERTY(EditAnywhere)
	float MaximumRange;
	
	UPROPERTY(EditAnywhere)
	float StopChasingRange;
	
	UPROPERTY(EditAnywhere)
	bool bIsValid = false;
	
	UPROPERTY(EditAnywhere)
	bool bIsExecuting = false;
};

UCLASS()
class HORDESHOOTER_API UEnemyWeaponController : public UPlayerWeaponController
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FPlanOfAttack CurrentPlan;
	
protected:
	UPROPERTY()
	TArray<UBaseEnemyAbility*> EnemyAbilities;
	
	UPROPERTY()
	TObjectPtr<ABasePaperEnemy> Owner;
	
public:
	virtual void Initialize(UWeaponData* WeaponToSet) override;
	
	virtual void StartAbility(int32 AbilityIndex, FVector OriginLocation, FVector TargetLocation, FVector UpVector = FVector::UpVector) override;
	
	virtual void Update(float DeltaTime) override;
	
	bool FormulatePlan(const APawn& Target);
	
protected:
	virtual void DebugWeaponPlan();
};
