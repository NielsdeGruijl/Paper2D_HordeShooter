// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerFlurry.h"

#include "PaperFlipbookComponent.h"
#include "DataAssets/DaggerFlurryData.h"
#include "Engine/OverlapResult.h"
#include "HordeShooter/Entities/Player/PlayerPaperCharacter.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"
#include "MVVM/Views/KeyRenderer.h"

void UDaggerFlurry::StartInternal(FVector EntityPosition, FVector AimPosition)
{
	Super::StartInternal(EntityPosition, AimPosition);
	
	if (CurrentAttackCombo >= MaxDaggerCombo && !bIsOnCooldown)
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimer, CooldownTimerDelegate, AbilityData->CooldownBetweenCombos, false);
		bIsOnCooldown = true;
		return;
	}
	
	if (bIsOnCooldown)
		return;
	
	GetWorld()->GetTimerManager().ClearTimer(StopComboTimer);
	
	if (!WeaponSprite)
	{
		if (APlayerPaperCharacter* Player = Cast<APlayerPaperCharacter>(Instigator))
			WeaponSprite = Player->WeaponSprite;
	}

	WeaponSprite->SetVisibility(false);
	
	FActorSpawnParameters SpawnParameters;
	
	TSubclassOf<ASpriteVFXActor> AttackVfx = AbilityData->AttackAnimations[CurrentAttackCombo];
	
	FVector AttackDirection = AimPosition - EntityPosition;
	
	FQuat Roll = FRotator(0, 0, -90).Quaternion();
	FQuat Pitch = FRotator(AttackDirection.Rotation().Yaw * -1, 0, 0).Quaternion();
	
	ASpriteVFXActor* VfxActor = GetWorld()->SpawnActor<ASpriteVFXActor>(
		AttackVfx, EntityPosition, FRotator(Roll * Pitch), SpawnParameters);
	
	CheckOverlaps(EntityPosition, FRotator(90, 0, 0).Quaternion() * FRotator(0, 0, AttackDirection.Rotation().Yaw * -1).Quaternion());
	
	CurrentAttackCombo++;
	
	GetWorld()->GetTimerManager().SetTimer(StopComboTimer, CooldownTimerDelegate, AbilityData->MaxTimeBetweenAttacks, false);
}

void UDaggerFlurry::Stop()
{
	Super::Stop();
	
	if (!WeaponSprite)
		return;
	
	WeaponSprite->SetVisibility(true);
}

void UDaggerFlurry::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
}

void UDaggerFlurry::Initialize(UBaseAbilityData* pAbilityData)
{
	Super::Initialize(pAbilityData);
	
	AbilityData = Cast<UDaggerFlurryData>(pAbilityData);
	
	MaxDaggerCombo = AbilityData->AttackAnimations.Num();
	
	CooldownTimerDelegate.BindLambda([this]
	{
		CurrentAttackCombo = 0;
		bIsOnCooldown = false;
	});
}

void UDaggerFlurry::CheckOverlaps(FVector Location, FQuat Rotation)
{
	TArray<FOverlapResult> Overlaps;
	
	FCollisionObjectQueryParams CollisionParams;
	CollisionParams.AddObjectTypesToQuery(ECC_Pawn);
	
	int i = CurrentAttackCombo >= MaxDaggerCombo - 1 ? 2 : 1;
		
	FCollisionShape Shape = FCollisionShape::MakeCapsule(100, 200);
	
	FCollisionQueryParams QueryParams;
	
	//DrawDebugCapsule(GetWorld(), Location, 200, 100, Rotation, FColor::Green, false, 1.0f);
	
	if (GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		Location,
		Rotation,
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
