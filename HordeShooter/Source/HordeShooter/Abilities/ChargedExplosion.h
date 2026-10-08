// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAbility.h"
#include "HordeShooter/Utils/CoroutineManager.h"
#include "ChargedExplosion.generated.h"

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
	
	ADecalActor* DecalActor;

	FVector FinalPosition;
	
	float CurrentExplosionRadius;

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
