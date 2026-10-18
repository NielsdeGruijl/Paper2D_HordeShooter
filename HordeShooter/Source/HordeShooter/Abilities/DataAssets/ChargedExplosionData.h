// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityData.h"
#include "HordeShooter/Runtime/MagicCircleDecal.h"
#include "ChargedExplosionData.generated.h"

class ADecalActor;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UChargedExplosionData : public UBaseAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMagicCircleDecal> OuterDecalActor;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMagicCircleDecal> InnerDecalActor;
	
	UPROPERTY(EditAnywhere)
	float ChargeDuration;
	
	UPROPERTY(EditAnywhere)
	float MaxInnerRotationSpeed;
	
	UPROPERTY(EditAnywhere)
	float MaxOuterRotationSpeed;
	
	UPROPERTY(EditAnywhere)
	float MaxDamage;
};
