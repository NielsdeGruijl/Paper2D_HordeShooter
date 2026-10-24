// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponAbility.h"

#include "DataAssets/BaseAbilityData.h"

bool UBaseWeaponAbility::Start(FVector EntityPosition, FVector AimPosition)
{
	if (bOnCooldown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is on cooldown"));
		return false;
	}
	
	StartInternal(EntityPosition, AimPosition);
	
	bOnCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, CooldownTimerDelegate, Data->Cooldown, false);
	
	return true;
}

void UBaseWeaponAbility::StartInternal(FVector EntityPosition, FVector AimPosition)
{
}

void UBaseWeaponAbility::Stop()
{
}

void UBaseWeaponAbility::Update(float DeltaTime)
{
}

void UBaseWeaponAbility::Initialize(UBaseAbilityData* pAbilityData)
{
	this->Data = pAbilityData;
	
	CooldownTimerDelegate.BindLambda([this]()
	{
		bOnCooldown = false;
	});
}

bool UBaseWeaponAbility::GetOnCooldown() const
{
	return bOnCooldown;
}
