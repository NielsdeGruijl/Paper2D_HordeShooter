// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponAbility.h"

void UBaseWeaponAbility::Start(FVector EntityPosition, FVector AimPosition)
{
	UE_LOG(LogTemp, Warning, TEXT("Starting Ability"));
}

void UBaseWeaponAbility::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping Ability"));
}

void UBaseWeaponAbility::Update(float DeltaTime)
{
}

void UBaseWeaponAbility::Initialize(UBaseAbilityData* AbilityData)
{
	this->Data = AbilityData;
}