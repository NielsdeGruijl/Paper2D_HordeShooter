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
	AActor* OwningActor;
	
private:
	UPROPERTY()
	UWeaponData* WeaponData;
	
	UPROPERTY()
	UBaseWeaponAbility* PrimaryAbility;
	
	UPROPERTY()
	UBaseWeaponAbility* SecondaryAbility;
	
public:
	void SetWeapon(UWeaponData* WeaponToSet);
	
	void StartPrimary();
	void StopPrimary();
	
	void StartSecondary();
	void StopSecondary();
	
	void Update(float DeltaTime);
	
private:
	FVector GetAimDirection();
	FVector GetMousePosition();
};
