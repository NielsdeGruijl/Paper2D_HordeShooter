// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedSlimeAttack.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HordeShooter/Abilities/DataAssets/Enemies/RangedSlimeAttackData.h"
#include "HordeShooter/Runtime/BaseProjectile.h"
#include "Kismet/GameplayStatics.h"

void URangedSlimeAttack::StartInternal(FVector OriginPosition, FVector TargetPosition, FVector UpVector, bool bIsDebugging)
{
	Super::StartInternal(OriginPosition, TargetPosition, UpVector, bIsDebugging);
		
	FVector Origin = OriginPosition;
	FVector Target = TargetPosition;
	
	FQuat Rotation = FQuat::Identity;
	
	if (UpVector != FVector::UpVector)
	{
		Rotation = FQuat::FindBetweenNormals(UpVector, FVector::UpVector);
	
		Origin = Rotation.RotateVector(OriginPosition);
		Target = Rotation.RotateVector(TargetPosition);
	}
	
	FVector LaunchVelocity;
	
	bool bFound = UGameplayStatics::SuggestProjectileVelocity_CustomArc(
		this,
		LaunchVelocity,
		Origin,
		Target,
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
	
	if (UpVector != FVector::UpVector)
		LaunchVelocity = Rotation.Inverse().RotateVector(LaunchVelocity);
	
	ProjectileObj->Initialize(AbilityData->Damage);
	
	ProjectileObj->Launch(LaunchVelocity, UpVector);
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
