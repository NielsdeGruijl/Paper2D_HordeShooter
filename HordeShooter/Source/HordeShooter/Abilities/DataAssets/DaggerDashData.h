// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityData.h"
#include "DaggerDashData.generated.h"

class ASpriteVFXActor;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UDaggerDashData : public UBaseAbilityData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Dash")
	TSubclassOf<ASpriteVFXActor> VFX;
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	float MaxDashDistance;
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	FLinearColor DashColor;
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashColourMultiplier;
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	float DashOpacity;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DashWidth;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	float ContactDamage;
};
