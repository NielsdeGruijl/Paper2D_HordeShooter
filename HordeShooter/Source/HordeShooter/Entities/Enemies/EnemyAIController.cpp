// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Navigation/CrowdManager.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StateTree = CreateDefaultSubobject<UStateTreeAIComponent>("StateTree");
	
	bStartAILogicOnPossess = true;
	
	bAttachToPawn = true;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UCrowdFollowingComponent* Crowd = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	Crowd->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
	Crowd->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	Crowd->SetCrowdSeparation(true);
	Crowd->SetCrowdSeparationWeight(5);
	Crowd->SetCrowdCollisionQueryRange(400.f);
	
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