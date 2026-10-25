// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneProjectile.h"

#include "DataAssets/ArcaneProjectileData.h"
#include "DataAssets/BaseAbilityData.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HordeShooter/Runtime/BaseProjectile.h"

void UArcaneProjectile::StartInternal(FVector EntityPosition, FVector AimPosition, FVector UpVector, bool bIsDebugging)
{
	Super::StartInternal(EntityPosition, AimPosition, UpVector, bIsDebugging);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Instigator;
	
	FVector AimDirection = AimPosition - EntityPosition;
	
	ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(
		AbilityData->Projectile, EntityPosition, FRotator::ZeroRotator, SpawnParameters);
	
	AimDirection.Normalize();
	
	if (!Projectile)
		return;
	
	Projectile->ProjectileMovementComponent->Velocity = AimDirection * Projectile->MovementSpeed;
	
	Projectile->PenetrationValue = 1;
}

void UArcaneProjectile::Stop()
{
}

void UArcaneProjectile::Initialize(UBaseAbilityData* PAbilityData)
{
	Super::Initialize(PAbilityData);
	
	AbilityData = Cast<UArcaneProjectileData>(PAbilityData);
}