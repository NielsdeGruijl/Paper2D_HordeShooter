// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePaperEnemy.h"
#include "RangedSlimeEnemy.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API ARangedSlimeEnemy : public ABasePaperEnemy
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ABaseProjectile> Projectile;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileArc;
	
public:
	virtual void BeginPlay() override;
	
	virtual void ExecuteAttackAction() override;
};
