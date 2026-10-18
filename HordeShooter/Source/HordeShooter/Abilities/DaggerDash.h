// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAbility.h"
#include "DaggerDash.generated.h"

class UBoxComponent;
class APlayerPaperCharacter;
class UDaggerDashData;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UDaggerDash : public UBaseWeaponAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UDaggerDashData* AbilityData;
	
	UPROPERTY()
	APlayerPaperCharacter* Player;
	
	UPROPERTY()
	UBoxComponent* DashCollision;
	
	FVector DashVector;

	FVector DashStartLocation;
	
	bool isDashing = false;
	
public:
	virtual void Start(FVector EntityPosition, FVector AimPosition) override;
	virtual void Stop() override;
	
	virtual void Update(float DeltaTime) override;
	
protected:
	void Initialize(UBaseAbilityData* pAbilityData) override;
	
	void UpdateDashCollisions();
};