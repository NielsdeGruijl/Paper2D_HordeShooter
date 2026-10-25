// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargedExplosion.h"

#include "DrawDebugHelpers.h"
#include "DataAssets/ChargedExplosionData.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"
#include "HordeShooter/Utils/CoroutineManager.h"
#include "HordeShooter/Runtime/MagicCircleDecal.h"

void UChargedExplosion::StartInternal(FVector EntityPosition, FVector AimPosition, FVector UpVector, bool bIsDebugging)
{
	Super::StartInternal(EntityPosition, AimPosition, UpVector, bIsDebugging);
	
	Update.BindUFunction(this, FName("UpdateCharge"));
	Complete.BindUFunction(this, FName("CompleteCharge"));
	
	ChargeCoroutine = GetWorld()->GetSubsystem<UCoroutineManager>()->StartCoroutine(
		AbilityData->ChargeDuration, &Update, &Complete);
	
	FActorSpawnParameters SpawnParameters;
	
	DecalActor = GetWorld()->SpawnActor<AMagicCircleDecal>(
		AbilityData->OuterDecalActor, AimPosition, FRotator::ZeroRotator, SpawnParameters);
	
	InnerDecalActor = GetWorld()->SpawnActor<AMagicCircleDecal>(
		AbilityData->InnerDecalActor, AimPosition, FRotator::ZeroRotator, SpawnParameters);
	
	CurrentExplosionRadius = 256;
	
	FinalPosition = AimPosition;
	ChargeProgress = 0;
}

void UChargedExplosion::Stop()
{
	Super::Stop();
	
	ExecuteExplosion();
	
	GetWorld()->GetSubsystem<UCoroutineManager>()->StopCoroutine(ChargeCoroutine);
	
	DecalActor->Destroy();
	InnerDecalActor->Destroy();
}

void UChargedExplosion::Initialize(UBaseAbilityData* PAbilityData)
{
	Super::Initialize(PAbilityData);
	
	AbilityData = Cast<UChargedExplosionData>(PAbilityData);
}

void UChargedExplosion::UpdateCharge(float DeltaTime)
{
	float Progress = DeltaTime / AbilityData->ChargeDuration;
	
	ChargeProgress = Progress;
	
	DecalActor->ChargeProgress = Progress * 3;
	InnerDecalActor->ChargeProgress = Progress * 3;
	
	DecalActor->RotationSpeed = Progress * AbilityData->MaxOuterRotationSpeed * -1;
	InnerDecalActor->RotationSpeed = Progress * AbilityData->MaxInnerRotationSpeed;
}

void UChargedExplosion::CompleteCharge()
{
}

void UChargedExplosion::ExecuteExplosion()
{
	TArray<FOverlapResult> Overlaps;
	
	FCollisionObjectQueryParams CollisionParams;
	CollisionParams.AddObjectTypesToQuery(ECC_Pawn);
	
	FCollisionShape Shape = FCollisionShape::MakeSphere(CurrentExplosionRadius);
	
	FCollisionQueryParams QueryParams;
	
	//DrawDebugSphere(GetWorld(), FinalPosition, CurrentExplosionRadius, 24, FColor::Green, false, 1.0f);
	
	if (GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		FinalPosition,
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
			
			HealthManager->TakeDamage(AbilityData->Damage * ChargeProgress);
		}
	}
}
