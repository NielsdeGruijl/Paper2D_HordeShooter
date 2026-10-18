// Fill out your copyright notice in the Description page of Project Settings.


#include "DaggerDash.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAssets/DaggerDashData.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HordeShooter/Entities/Player/PlayerPaperCharacter.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"
#include "HordeShooter/Runtime/SpriteVFXActor.h"

void UDaggerDash::Start(FVector EntityPosition, FVector AimPosition)
{
	Super::Start(EntityPosition, AimPosition);
	
	if (!Player)
	{
		APlayerPaperCharacter* TempPlayer = Cast<APlayerPaperCharacter>(Instigator);
		if (!TempPlayer)
			return;
		
		Player = TempPlayer;
	}

	DashVector = AimPosition - Player->GetActorLocation();;
	
	DashVector.Normalize();
	DashVector *= AbilityData->MaxDashDistance;
	
	Player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	Player->LaunchCharacter(DashVector, false, false);
	
	Player->SetSpriteFlash(AbilityData->DashColourMultiplier, AbilityData->DashColor);
	Player->SetSpriteOpacity(AbilityData->DashOpacity);
	
	DashStartLocation = Player->GetActorLocation();
	
	if (AbilityData->VFX)
	{
		FActorSpawnParameters SpawnParameters;
	
		FVector AttackDirection = AimPosition - EntityPosition;
	
		FQuat Roll = FRotator(0, 0, -90).Quaternion();
		FQuat Pitch = FRotator(AttackDirection.Rotation().Yaw * -1, 0, 0).Quaternion();
	
		ASpriteVFXActor* VfxActor = GetWorld()->SpawnActor<ASpriteVFXActor>(
			AbilityData->VFX, EntityPosition, FRotator(Roll * Pitch), SpawnParameters);
	
		FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, false);
		VfxActor->AttachToActor(Player, TransformRules);
	}
	
	Player->WeaponSprite->SetVisibility(false);
	
	isDashing = true;
}

void UDaggerDash::Stop()
{
	Super::Stop();
}

void UDaggerDash::Update(float DeltaTime)
{
	Super::Update(DeltaTime);
	
	if (!Player || !isDashing)
		return;
	
	float Velocity = Player->GetVelocity().Length();
	
	if (Velocity <= Player->GetCharacterMovement()->MaxWalkSpeed)
	{
		Player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	
		Player->SetSpriteFlash(0, AbilityData->DashColor);
		Player->SetSpriteOpacity(1);
		
		Player->WeaponSprite->SetVisibility(true);
		
		UpdateDashCollisions();
		
		isDashing = false;
	}
}

void UDaggerDash::Initialize(UBaseAbilityData* pAbilityData)
{
	Super::Initialize(pAbilityData);
	
	AbilityData = Cast<UDaggerDashData>(pAbilityData);
}

void UDaggerDash::UpdateDashCollisions()
{
	if (!Player)
		return;
	
	const FVector Start = DashStartLocation;
	const FVector End = Player->GetActorLocation();
	
	const FVector Center = (Start + End) * 0.5f;

	const FQuat Rotation = FRotationMatrix::MakeFromZ(End - Start).ToQuat();
	
	float HalfHeight = (End-Start).Length() * 0.5f + AbilityData->DashWidth;
	const FCollisionShape Shape = FCollisionShape::MakeCapsule(AbilityData->DashWidth, HalfHeight);
	
	FCollisionQueryParams Params(SCENE_QUERY_STAT(DashTube), false, Player);
	FCollisionObjectQueryParams ObjParams(ECC_Pawn);
	
	TArray<FOverlapResult> HitResults;
	GetWorld()->OverlapMultiByObjectType(HitResults, Center, Rotation, ObjParams, Shape, Params);
	
	//DrawDebugCapsule(GetWorld(), Center, HalfHeight, AbilityData->DashWidth, Rotation, FColor::Red, false, 2.f);
	
	for (const FOverlapResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor == Player)
			continue;
		
		if (UHealthManager* HealthManager = HitActor->FindComponentByClass<UHealthManager>())
		{
			HealthManager->TakeDamage(AbilityData->ContactDamage);
		}
	}
}
