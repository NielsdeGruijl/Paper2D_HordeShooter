// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeSlimeAttack.h"

#include "Engine/OverlapResult.h"
#include "HordeShooter/Abilities/DataAssets/Enemies/MeleeAttackData.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"

void UMeleeSlimeAttack::StartInternal(FVector OriginPosition, FVector TargetPosition)
{
	Super::StartInternal(OriginPosition, TargetPosition);
	
	TArray<FOverlapResult> Overlaps;
	
	FCollisionObjectQueryParams CollisionParams;
	CollisionParams.AddObjectTypesToQuery(ECC_Pawn);
	
	FCollisionShape Shape = FCollisionShape::MakeBox(AbilityData->MeleeHitboxBounds);
	
	FCollisionQueryParams QueryParams;
	
	DrawDebugBox(GetWorld(), OriginPosition, AbilityData->MeleeHitboxBounds, FQuat::Identity, FColor::Green, false, 1.0f);
	
	if (GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		OriginPosition,
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
			
			HealthManager->TakeDamage(AbilityData->Damage);
		}
	}
}

void UMeleeSlimeAttack::Stop()
{
	Super::Stop();
}

void UMeleeSlimeAttack::Initialize(UBaseAbilityData* pAbilityData)
{
	Super::Initialize(pAbilityData);
	
	AbilityData = Cast<UMeleeAttackData>(pAbilityData);
}
