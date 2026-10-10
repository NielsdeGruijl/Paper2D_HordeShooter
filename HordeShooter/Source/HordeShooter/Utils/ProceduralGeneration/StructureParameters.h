// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StructureParameters.generated.h"

/**
 * 
 */
USTRUCT()
struct HORDESHOOTER_API FStructureParameters
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int CellSize = 400;
	
	// Structure dimensions in grid cells
	UPROPERTY(EditAnywhere)
	FVector StructureDimensions;
	
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UStaticMesh>> Walls;
};