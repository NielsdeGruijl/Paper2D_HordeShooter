// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargedExplosion.h"

#include "DrawDebugHelpers.h"
#include "DataAssets/ChargedExplosionData.h"
#include "Engine/DecalActor.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"
#include "HordeShooter/Utils/CoroutineManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UChargedExplosion::Start(FVector EntityPosition, FVector AimPosition)
{
	Super::Start(EntityPosition, AimPosition);
	
	Update.BindUFunction(this, FName("UpdateCharge"));
	Complete.BindUFunction(this, FName("CompleteCharge"));
	
	ChargeCoroutine = GetWorld()->GetSubsystem<UCoroutineManager>()->StartCoroutine(
		AbilityData->ChargeDuration, &Update, &Complete);
	
	FActorSpawnParameters SpawnParameters;
	
	DecalActor = GetWorld()->SpawnActor<ADecalActor>(
		AbilityData->DecalActor, AimPosition, FRotator::ZeroRotator, SpawnParameters);
	
	DecalActor->SetActorScale3D(FVector(5, AbilityData->MinDecalSize, AbilityData->MinDecalSize));
	
	FinalPosition = AimPosition;
}

void UChargedExplosion::Stop()
{
	Super::Stop();
	
	ExecuteExplosion();
	
	GetWorld()->GetSubsystem<UCoroutineManager>()->StopCoroutine(ChargeCoroutine);
	DecalActor->Destroy();
}

void UChargedExplosion::Initialize(UBaseAbilityData* PAbilityData)
{
	Super::Initialize(PAbilityData);
	
	AbilityData = Cast<UChargedExplosionData>(PAbilityData);
}

void UChargedExplosion::UpdateCharge(float DeltaTime)
{
	float Progress = DeltaTime / AbilityData->ChargeDuration;
	float CurrentDecalSize = Progress * (AbilityData->MaxDecalSize - AbilityData->MinDecalSize) + AbilityData->MinDecalSize;
	
	CurrentExplosionRadius = CurrentDecalSize * 100;
	
	DecalActor->SetActorScale3D(FVector(5, CurrentDecalSize, CurrentDecalSize));
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
			
			UActorComponent* Component = Result.GetActor()->GetComponentByClass(UHealthManager::StaticClass());
			
			if (!Component)
				continue;
			
			UHealthManager* HealthManager = Cast<UHealthManager>(Component);
			HealthManager->TakeDamage(10);
		}
	}
}
