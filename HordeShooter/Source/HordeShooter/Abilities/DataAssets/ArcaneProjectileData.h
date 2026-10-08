// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityData.h"
#include "ArcaneProjectileData.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UArcaneProjectileData : public UBaseAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseProjectile> Projectile;
	
};
