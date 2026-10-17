// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneProjectile.h"

#include "DataAssets/ArcaneProjectileData.h"
#include "DataAssets/BaseAbilityData.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HordeShooter/Runtime/BaseProjectile.h"

void UArcaneProjectile::Start(FVector EntityPosition, FVector AimPosition)
{
	Super::Start(EntityPosition, AimPosition);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Instigator;
	
	FVector AimDirection = AimPosition - EntityPosition;
	FRotator AimRotation = AimDirection.Rotation();
	
	/*EntityPosition = FVector(
		EntityPosition.X, 
		EntityPosition.Y, 
		0.3f);*/
	
	ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(
		AbilityData->Projectile, EntityPosition, FRotator::ZeroRotator, SpawnParameters);
	
	AimDirection.Normalize();
	
	Projectile->ProjectileMovementComponent->Velocity = AimDirection * Projectile->MovementSpeed;
}

void UArcaneProjectile::Stop()
{
}

void UArcaneProjectile::Initialize(UBaseAbilityData* PAbilityData)
{
	Super::Initialize(PAbilityData);
	
	AbilityData = Cast<UArcaneProjectileData>(PAbilityData);
}