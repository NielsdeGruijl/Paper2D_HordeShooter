// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAbility.h"
#include "DaggerFlurry.generated.h"

class UPaperFlipbookComponent;
class UDaggerFlurryData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UDaggerFlurry : public UBaseWeaponAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UDaggerFlurryData* AbilityData;
	
	UPROPERTY()
	UPaperFlipbookComponent* WeaponSprite;
	
	FTimerHandle CooldownTimer;
	FTimerDelegate CooldownTimerDelegate;
	
	FTimerHandle StopComboTimer;
	
	bool bIsOnCooldown;
	
	float MaxDaggerCombo;
	float CurrentAttackCombo = 0;
	
public:
	virtual void Start(FVector EntityPosition, FVector AimPosition) override;
	virtual void Stop() override;
	
	virtual void Update(float DeltaTime) override;
	
protected:
	void Initialize(UBaseAbilityData* pAbilityData) override;
	
	void CheckOverlaps(FVector Location, FQuat Rotation);
	
};
