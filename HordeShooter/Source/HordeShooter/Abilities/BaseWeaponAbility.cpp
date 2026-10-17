// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponAbility.h"

void UBaseWeaponAbility::Start(FVector EntityPosition, FVector AimPosition)
{
}

void UBaseWeaponAbility::Stop()
{
}

void UBaseWeaponAbility::Update(float DeltaTime)
{
}

void UBaseWeaponAbility::Initialize(UBaseAbilityData* AbilityData)
{
	this->Data = AbilityData;
}