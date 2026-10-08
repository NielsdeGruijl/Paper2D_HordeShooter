// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "Abilities/BaseWeaponAbility.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

class UBaseAbilityData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	UPaperSprite* WeaponSprite;
	
	UPROPERTY(EditAnywhere)
	UBaseAbilityData* PrimaryAbilityData;
		
	UPROPERTY(EditAnywhere)
	UBaseAbilityData* SecondaryAbilityData;
	
	UPROPERTY(EditAnywhere)
	float Damage;
	
	void CreateWeapon();
};
