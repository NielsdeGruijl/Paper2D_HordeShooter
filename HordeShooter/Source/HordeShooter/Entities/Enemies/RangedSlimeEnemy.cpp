// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedSlimeEnemy.h"

#include "EnemyAIController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HordeShooter/Runtime/BaseProjectile.h"
#include "Kismet/GameplayStatics.h"

void ARangedSlimeEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ARangedSlimeEnemy::ExecuteAttackAction()
{
	Super::ExecuteAttackAction();
	
	if (!TargetToAttack)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy attack target is null"));
		return;
	}
	
	FVector LaunchVelocity;
	
	bool bFound = UGameplayStatics::SuggestProjectileVelocity_CustomArc(
		this,
		LaunchVelocity,
		GetActorLocation(),
		TargetToAttack->GetActorLocation(),
		GetWorld()->GetGravityZ(),
		ProjectileArc);
	
	if (!bFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("No projectile launch velocity found"))
		return;
	}
	
	ABaseProjectile* ProjectileObj = GetWorld()->SpawnActor<ABaseProjectile>(
		Projectile,
		GetActorLocation(),
		FRotator(0.0f,0.0f,0.0f));
	
	ProjectileObj->ProjectileMovementComponent->Velocity = LaunchVelocity;
}
