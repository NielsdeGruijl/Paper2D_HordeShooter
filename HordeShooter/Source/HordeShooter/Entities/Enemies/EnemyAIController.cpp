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
	
	//HealthManager = InPawn->FindComponentByClass<UHealthManager>();
	
	/*if (HealthManager)
	{
		HealthManager->OnHealthChanged.AddUObject(this, &AEnemyAIController::OnPawnHealthChanged);
	}*/
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
	
}

void AEnemyAIController::OnPawnHealthChanged(float NewHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("New heatlh: %f"), NewHealth);
}



