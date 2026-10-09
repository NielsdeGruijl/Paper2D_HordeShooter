// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetourCrowdAIController.h"
#include "Components/StateTreeAIComponent.h"
#include "EnemyAIController.generated.h"

class UHealthManager;

/**
 * 
 */

// Change to use ADetourCrowdAIController

UCLASS()
class HORDESHOOTER_API AEnemyAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	APawn* ControlledPawn;
	
	UPROPERTY()
	TObjectPtr<UHealthManager> HealthManager;
	
public:
	AEnemyAIController();
	
	UPROPERTY(EditAnywhere)
	UStateTreeAIComponent* StateTree;
	
public:
	void OnPossess(APawn* InPawn) override;
	
	void OnUnPossess() override;
	
protected:
	void OnPawnHealthChanged(float NewHealth);

};
