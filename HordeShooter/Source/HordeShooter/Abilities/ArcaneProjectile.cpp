// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneProjectile.h"

#include "DataAssets/ArcaneProjectileData.h"
#include "DataAssets/BaseAbilityData.h"
#include "Engine/World.h"
#include "HordeShooter/Runtime/BaseProjectile.h"

void UArcaneProjectile::Start(FVector EntityPosition, FVector AimPosition)
{
	Super::Start(EntityPosition, AimPosition);
	UE_LOG(LogTemp, Warning, TEXT("StartPrimaryAbility"));
	
	FActorSpawnParameters SpawnParameters;
	
	FVector AimDirection = AimPosition - EntityPosition;
	FRotator AimRotation = AimDirection.Rotation();
	
	GetWorld()->SpawnActor<ABaseProjectile>(
		AbilityData->Projectile, EntityPosition, AimRotation, SpawnParameters);
}

void UArcaneProjectile::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("StopPrimaryAbility"));
}

void UArcaneProjectile::Initialize(UBaseAbilityData* PAbilityData)
{
	Super::Initialize(PAbilityData);
	
	AbilityData = Cast<UArcaneProjectileData>(PAbilityData);
}