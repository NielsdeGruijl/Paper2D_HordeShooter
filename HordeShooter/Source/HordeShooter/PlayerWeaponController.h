// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.h"
#include "UObject/Object.h"
#include "PlayerWeaponController.generated.h"


class UBaseWeaponAbility;

UCLASS()
class HORDESHOOTER_API UPlayerWeaponController : public UObject
{
	GENERATED_BODY()
	
public:
	UPlayerWeaponController();
	
	UPROPERTY()
	APawn* OwningPawn;
	
	bool* bIsDebugging;
	
protected:
	UPROPERTY()
	UWeaponData* WeaponData;
	
	UPROPERTY()
	TArray<UBaseWeaponAbility*> Abilities;
	
public:
	virtual void Initialize(UWeaponData* WeaponToSet);
	
	bool CanStartAbility(int32 AbilityIndex) const;
	
	virtual void StartAbility(int32 AbilityIndex, FVector OriginLocation, FVector TargetLocation, FVector UpVector = FVector::UpVector);
	virtual void StopAbility(int32 AbilityIndex);
	
	virtual void Update(float DeltaTime);
	
protected:
	FVector GetAimDirection();
	FVector GetMousePosition();
};
