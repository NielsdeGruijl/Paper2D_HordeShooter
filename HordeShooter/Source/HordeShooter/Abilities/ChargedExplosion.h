// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAbility.h"
#include "HordeShooter/Utils/CoroutineManager.h"
#include "ChargedExplosion.generated.h"

class AMagicCircleDecal;
class ADecalActor;
class UChargedExplosionData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UChargedExplosion : public UBaseWeaponAbility
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UChargedExplosionData* AbilityData;
	
	AMagicCircleDecal* DecalActor;
	AMagicCircleDecal* InnerDecalActor;

	FVector FinalPosition;
	
	float CurrentExplosionRadius;
	
	float ChargeProgress = 0;

public:
	void Start(FVector EntityPosition, FVector AimPosition) override;
	void Stop() override;
	
protected:
	void Initialize(UBaseAbilityData* PAbilityData) override;
	
	UFUNCTION()
	void UpdateCharge(float DeltaTime);
	
	UFUNCTION()
	void CompleteCharge();
	
	void ExecuteExplosion();
	
	CoroutineUpdate Update;
	CoroutineComplete Complete;
	
private:
	TWeakPtr<Coroutine> ChargeCoroutine;
};
