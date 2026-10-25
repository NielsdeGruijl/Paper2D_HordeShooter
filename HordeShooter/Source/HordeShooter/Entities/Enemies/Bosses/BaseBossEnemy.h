// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperEnemy.h"
#include "BaseBossEnemy.generated.h"

class UPlayerWeaponController;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API ABaseBossEnemy : public ABasePaperEnemy
{
	GENERATED_BODY()

public:
	ABaseBossEnemy();
	virtual void BeginPlay() override;
	
	virtual void ExecuteAttackAction() override;
};
