// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "Navigation/CrowdFollowingComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StateTree = CreateDefaultSubobject<UStateTreeAIComponent>("StateTree");
	
	bStartAILogicOnPossess = true;
	
	bAttachToPawn = true;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	UCrowdFollowingComponent* Crowd = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	Crowd->SetCrowdSimulationState(ECrowdSimulationState::Enabled);
	Crowd->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	Crowd->SetCrowdSeparation(true);
	Crowd->SetCrowdSeparationWeight(5);
	Crowd->SetCrowdCollisionQueryRange(400.f);
	
	//UE_LOG(LogTemp, Error, TEXT("STARTING STATETREE LOGIC"))
	Super::OnPossess(InPawn);
	//UE_LOG(LogTemp, Error, TEXT("FINISHED STARTING STATETREE LOGIC"))
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyAIController::OnPawnHealthChanged(float NewHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("New heatlh: %f"), NewHealth);
}