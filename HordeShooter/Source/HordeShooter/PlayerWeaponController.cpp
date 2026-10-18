// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponController.h"

#include "Abilities/DataAssets/BaseAbilityData.h"
#include "Engine/World.h"

UPlayerWeaponController::UPlayerWeaponController()
{
}

void UPlayerWeaponController::SetWeapon(UWeaponData* WeaponToSet)
{
	WeaponData = WeaponToSet;
	
	PrimaryAbility = WeaponData->PrimaryAbilityData->CreateAbility(this);
	
	if (PrimaryAbility)
		PrimaryAbility->Instigator = OwningPawn;
	
	SecondaryAbility = WeaponData->SecondaryAbilityData->CreateAbility(this);
	
	if (SecondaryAbility)
		SecondaryAbility->Instigator = OwningPawn;
}

void UPlayerWeaponController::StartPrimary()
{
	PrimaryAbility->Start(ProjectileOrigin->GetComponentLocation(), GetMousePosition() + FVector::ZAxisVector * ProjectileOrigin->GetComponentLocation().Z);
}

void UPlayerWeaponController::StopPrimary()
{
	PrimaryAbility->Stop();
}

void UPlayerWeaponController::StartSecondary()
{
	SecondaryAbility->Start(ProjectileOrigin->GetComponentLocation(), GetMousePosition() + FVector::ZAxisVector * ProjectileOrigin->GetComponentLocation().Z);
}

void UPlayerWeaponController::StopSecondary()
{
	SecondaryAbility->Stop();
}

void UPlayerWeaponController::Update(float DeltaTime)
{
	PrimaryAbility->Update(DeltaTime);
	SecondaryAbility->Update(DeltaTime);
}

FVector UPlayerWeaponController::GetAimDirection()
{
	FVector MousePosition = GetMousePosition();
	
	FVector AimDirection = MousePosition - OwningPawn->GetActorLocation();
	
	return AimDirection;
}

FVector UPlayerWeaponController::GetMousePosition()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController())
		return FVector::ZeroVector;
	
	FHitResult Hit;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Hit);
	
	if (!Hit.bBlockingHit)
		return FVector::ZeroVector;
	
	FVector Position = Hit.Location;
	
	Position = FVector(Position.X, Position.Y, 0);
	
	return Position;
}
