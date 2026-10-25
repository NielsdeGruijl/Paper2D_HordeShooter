// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBossEnemy.h"

#include "PaperFlipbookComponent.h"
#include "HordeShooter/EnemyWeaponController.h"

ABaseBossEnemy::ABaseBossEnemy()
{
}

void ABaseBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBossEnemy::ExecuteAttackAction()
{
	if (!WeaponController)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon controller is nullptr"));
		return;
	}
	
	WeaponController->StartAbility(CurrentAbilityIndex, AttackOrigin->GetComponentLocation(), TargetToAttack->GetActorLocation(), Sprite->GetUpVector());
}
