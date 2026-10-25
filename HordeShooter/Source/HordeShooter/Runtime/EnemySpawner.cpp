// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "PaperFlipbookComponent.h"
#include "HordeShooter/Entities/DataAssets/EnemySpawnCard.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy(UEnemySpawnCard* SpawnCard, TObjectPtr<APawn> DefaultTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning enemy!"))
	
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = GetActorLocation() + FVector(0,0,SpawnCard->ZOffset);
	
	GetWorld()->SpawnActor<ABasePaperEnemy>(SpawnCard->EnemyClass, SpawnLocation, GetActorRotation(), SpawnParams)->PullAggro(DefaultTarget);
}