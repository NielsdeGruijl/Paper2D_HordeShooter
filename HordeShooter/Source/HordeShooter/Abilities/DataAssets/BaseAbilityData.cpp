// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbilityData.h"

#include "HordeShooter/Abilities/BaseWeaponAbility.h"

UBaseWeaponAbility* UBaseAbilityData::CreateAbility(UObject* Owner)
{
	UBaseWeaponAbility* Ability = NewObject<UBaseWeaponAbility>(Owner, AbilityClass);
	Ability->Initialize(this);
	
	return Ability;
}
