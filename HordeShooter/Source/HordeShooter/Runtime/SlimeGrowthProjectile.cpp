// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeGrowthProjectile.h"

#include "Engine/OverlapResult.h"
#include "HordeShooter/Entities/DataAssets/EnemySpawnCard.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"


void ASlimeGrowthProjectile::Initialize(float Damage, float ImpactRadius)
{
	Super::Initialize(Damage);
	
	ImpactSphereRadius = 50000;
}

void ASlimeGrowthProjectile::OnOverlapInternal(AActor* OtherActor)
{
	TArray<FOverlapResult> Overlaps;
	
	FCollisionObjectQueryParams CollisionParams;
	CollisionParams.AddObjectTypesToQuery(ECC_Pawn);
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(ImpactSphereRadius);
	
	FCollisionQueryParams QueryParams;
	
	DrawDebugSphere(GetWorld(), GetActorLocation(), ImpactSphereRadius, 24, FColor::Green, false, 1.0f);
	
	if (GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		GetActorLocation(),
		FQuat::Identity,
		CollisionParams,
		Shape,
		QueryParams))
	{
		for (FOverlapResult& Result : Overlaps)
		{
			AActor* Actor = Result.GetActor();
			
			if (!Actor)
				continue;
			
			UHealthManager* HealthManager = Result.GetActor()->FindComponentByClass<UHealthManager>();
			
			if (!HealthManager)
				continue;
			
			HealthManager->TakeDamage(ImpactDamage);
		}
	}
	
	if (EnemyTypesToSpawn.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No available enemies to spawn"));
		return;
	}
	
	float CurrentCredits = EnemySpawnCredits;
	TArray<UEnemySpawnCard*> SpawnCardCandidates;
	
	for (UEnemySpawnCard* SpawnCard : EnemyTypesToSpawn)
	{
		if (CurrentCredits < SpawnCard->CreditCost)
			continue;
		
		SpawnCardCandidates.Add(SpawnCard);
	}
	
	UEnemySpawnCard* SpawnCard = EnemyTypesToSpawn[0];
	
	if (SpawnCardCandidates.Num() != 0)
	{
		int CardIndex = FMath::RandRange(0, SpawnCardCandidates.Num() - 1);
		SpawnCard = SpawnCardCandidates[CardIndex];
	}
	
	int EnemiesSpawned = 0;
	while (CurrentCredits >= SpawnCard->CreditCost && EnemiesSpawned < MaxEnemiesToSpawn)
	{
		CurrentCredits -= SpawnCard->CreditCost;
		
		SpawnEnemy(SpawnCard);
		
		EnemiesSpawned++;
	}
	
	// Guarantee 1 enemy always spawns
	if (EnemiesSpawned <= 0)
	{
		SpawnEnemy(SpawnCard);
	}
}

void ASlimeGrowthProjectile::SpawnEnemy(UEnemySpawnCard* Card)
{
	FActorSpawnParameters SpawnParams;
	
	const FVector2D Offset2D = FMath::RandPointInCircle(ImpactSphereRadius);
	FVector SpawnLocation = GetActorLocation() + FVector(Offset2D.X, Offset2D.Y, 0.f);
	
	UE_LOG(LogTemp, Warning, TEXT("Spawn X: %f, Y: %f, Z: %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
	
	FCollisionObjectQueryParams CollisionParams;
	CollisionParams.AddObjectTypesToQuery(ECC_WorldStatic);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	FHitResult HitResult;
	bool bFound = GetWorld()->LineTraceSingleByObjectType(HitResult, SpawnLocation, SpawnLocation - FVector::UpVector * 100000, CollisionParams, QueryParams);
	
	if (bFound)
		SpawnLocation.Z = HitResult.ImpactPoint.Z + Card->ZOffset;
	
	GetWorld()->SpawnActor<ABasePaperEnemy>(Card->EnemyClass, SpawnLocation, GetActorRotation(), SpawnParams);
}
