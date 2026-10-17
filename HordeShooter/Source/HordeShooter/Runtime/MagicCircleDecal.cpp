// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicCircleDecal.h"

#include "Components/BillboardComponent.h"
#include "Components/DecalComponent.h"

AMagicCircleDecal::AMagicCircleDecal(const FObjectInitializer& OI)
	: Super(OI)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMagicCircleDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorWorldRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
}
