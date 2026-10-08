// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityData.h"
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
	TSubclassOf<ADecalActor> DecalActor;
	
	UPROPERTY(EditAnywhere)
	float ChargeDuration;
	
	UPROPERTY(EditAnywhere)
	float MinDecalSize;
	
	UPROPERTY(EditAnywhere)
	float MaxDecalSize;
};
