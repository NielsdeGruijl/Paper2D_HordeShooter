// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MagicCircleDecal.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API AMagicCircleDecal : public ADecalActor
{
	GENERATED_BODY()
	
public:
	float RotationSpeed;
	
	UPROPERTY(BlueprintReadOnly)
	float ChargeProgress;
	
public:
	AMagicCircleDecal(const FObjectInitializer& OI);
	
	virtual void Tick(float DeltaTime) override;
};
