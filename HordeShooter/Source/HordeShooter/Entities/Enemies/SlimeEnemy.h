// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePaperEnemy.h"
#include "SlimeEnemy.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API ASlimeEnemy : public ABasePaperEnemy
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* AttackCollider;
	
public:
	ASlimeEnemy();
	
	virtual void BeginPlay() override;
	
	virtual void ExecuteAttackAction() override;
	
	virtual void Death() override;
};
