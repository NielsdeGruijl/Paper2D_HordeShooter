// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedSlimeAttack.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "HordeShooter/Abilities/DataAssets/Enemies/RangedSlimeAttackData.h"
#include "HordeShooter/Runtime/BaseProjectile.h"
#include "Kismet/GameplayStatics.h"

void URangedSlimeAttack::StartInternal(FVector OriginPosition, FVector TargetPosition)
{
	Super::StartInternal(OriginPosition, TargetPosition);
		
	FVector LaunchVelocity;
	
	bool bFound = UGameplayStatics::SuggestProjectileVelocity_CustomArc(
		this,
		LaunchVelocity,
		OriginPosition,
		TargetPosition,
		GetWorld()->GetGravityZ(),
		AbilityData->ProjectileArc);
	
	if (!bFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("No projectile launch velocity found"))
		return;
	}
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = Instigator;
	
	ABaseProjectile* ProjectileObj = GetWorld()->SpawnActor<ABaseProjectile>(
		AbilityData->ProjectileClass,
		OriginPosition,
		FRotator(0.0f,0.0f,0.0f),
		SpawnInfo);
	
	if (!ProjectileObj)
		return;
	
	ProjectileObj->ProjectileMovementComponent->Velocity = LaunchVelocity;
}

void URangedSlimeAttack::Stop()
{
	Super::Stop();
}

void URangedSlimeAttack::Initialize(UBaseAbilityData* pAbilityData)
{
	Super::Initialize(pAbilityData);
	
	AbilityData = Cast<URangedSlimeAttackData>(pAbilityData);
}
