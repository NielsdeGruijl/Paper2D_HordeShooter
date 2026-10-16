// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "../Systems/HealthManager.h"


AEnemyAIController::AEnemyAIController()
{
	StateTree = CreateDefaultSubobject<UStateTreeAIComponent>("StateTree");
	
	bStartAILogicOnPossess = true;
	
	bAttachToPawn = true;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	StateTree->StartLogic();
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
	
}

void AEnemyAIController::OnPawnHealthChanged(float NewHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("New heatlh: %f"), NewHealth);
}