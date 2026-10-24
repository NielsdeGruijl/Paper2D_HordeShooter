// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeaponController.h"

#include "Abilities/DataAssets/BaseAbilityData.h"
#include "Engine/World.h"

UPlayerWeaponController::UPlayerWeaponController()
{
}

void UPlayerWeaponController::Initialize(UWeaponData* WeaponToSet)
{
	WeaponData = WeaponToSet;
	
	for (int32 i = 0; i < WeaponData->Abilities.Num(); i++)
	{
		Abilities.Add(WeaponData->Abilities[i]->CreateAbility(this));
		Abilities[i]->Instigator = OwningPawn;
	}
}

bool UPlayerWeaponController::CanStartAbility(int32 AbilityIndex) const
{
	if (AbilityIndex >= Abilities.Num() || !Abilities[AbilityIndex])
	{
		UE_LOG(LogTemp,Warning, TEXT("AbilityIndex is out of range or Ability does not exist"))
		return false;
	}
	
	return !Abilities[AbilityIndex]->GetOnCooldown();
}

void UPlayerWeaponController::StartAbility(int32 AbilityIndex, FVector OriginLocation, FVector TargetLocation)
{
	if (AbilityIndex >= Abilities.Num() || !Abilities[AbilityIndex])
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not start ability, AbilityIndex is out of range or Ability does not exist"))
		return;
	}
	
	Abilities[AbilityIndex]->Start(OriginLocation, TargetLocation);
}

void UPlayerWeaponController::StopAbility(int32 AbilityIndex)
{
	if (AbilityIndex >= Abilities.Num() || !Abilities[AbilityIndex])
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not stop ability, AbilityIndex is out of range or Ability does not exist"))
		return;
	}
	
	Abilities[AbilityIndex]->Stop();
}

void UPlayerWeaponController::Update(float DeltaTime)
{
	for (UBaseWeaponAbility* Ability : Abilities)
	{
		if (!Ability)
			continue;
		
		Ability->Update(DeltaTime);
	}
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
