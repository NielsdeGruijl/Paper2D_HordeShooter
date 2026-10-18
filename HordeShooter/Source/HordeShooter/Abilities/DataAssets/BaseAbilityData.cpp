// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilityData.h"

#include "HordeShooter/Abilities/BaseWeaponAbility.h"

UBaseWeaponAbility* UBaseAbilityData::CreateAbility(UObject* Owner)
{
	if (!AbilityClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Fuckass Unreal Engine deleted your ability class again"));
		return nullptr;
	}
	
	UBaseWeaponAbility* Ability = NewObject<UBaseWeaponAbility>(Owner, AbilityClass);
	Ability->Initialize(this);
	
	return Ability;
}
