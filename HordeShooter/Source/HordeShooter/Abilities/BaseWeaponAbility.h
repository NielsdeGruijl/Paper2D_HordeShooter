// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseWeaponAbility.generated.h"

class UBaseAbilityData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UBaseWeaponAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	APawn* Instigator;
	
private:
	UPROPERTY()
	UBaseAbilityData* Data;

public:
	virtual void Start(FVector EntityPosition, FVector AimPosition);
	virtual void Stop();
	
	virtual void Update(float DeltaTime);
	
	virtual void Initialize(UBaseAbilityData* AbilityData);
};
