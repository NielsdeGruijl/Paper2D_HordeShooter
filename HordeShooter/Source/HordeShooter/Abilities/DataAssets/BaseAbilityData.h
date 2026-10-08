// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseAbilityData.generated.h"

class UBaseWeaponAbility;
class ABaseProjectile;

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UBaseAbilityData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseWeaponAbility> AbilityClass;
	
	UFUNCTION()
	UBaseWeaponAbility* CreateAbility(UObject* Owner);
};
