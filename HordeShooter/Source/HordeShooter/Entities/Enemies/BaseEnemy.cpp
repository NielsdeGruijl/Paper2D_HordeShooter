// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "BaseEnemy.h"

#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "Elements/Framework/TypedElementSorter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");
	Health= CreateDefaultSubobject<UHealthManager>("Health");
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("PaperFlipBook");
	FlipbookComponent->SetupAttachment(RootComponent);
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MovementComponent->MaxSpeed = MaxMoveSpeed;
	
	//PlayAnimation(EEnemyAnimation::Idle);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::PlayAnimation(EEnemyAnimation Animation)
{
	UPaperFlipbook* NewFlipbook = Animations[Animation];
	
	if (FlipbookComponent->GetFlipbook() == NewFlipbook)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("NEW ANIMATION: %d"), Animation);
	
	FlipbookComponent->SetFlipbook(NewFlipbook);
	
}

void ABaseEnemy::PerformAttack()
{
	PlayAnimation(EEnemyAnimation::Attack);
	
}
