// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAbility.h"
#include "ArcaneProjectile.generated.h"

class UArcaneProjectileData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UArcaneProjectile : public UBaseWeaponAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UArcaneProjectileData* AbilityData;
	
public:
	void Start(FVector EntityPosition, FVector AimPosition) override;
	void Stop() override;
	
protected:
	void Initialize(UBaseAbilityData* PAbilityData) override;
};
