// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityData.h"
#include "HordeShooter/Runtime/SpriteVFXActor.h"
#include "DaggerFlurryData.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UDaggerFlurryData : public UBaseAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASpriteVFXActor>> AttackAnimations;
	
	UPROPERTY(EditAnywhere)
	float CooldownBetweenCombos;
	
	UPROPERTY(EditAnywhere)
	float MaxTimeBetweenAttacks;
	
	UPROPERTY(EditAnywhere)
	float Damage;
};
