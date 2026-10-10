// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FGridCell;
/**
 * 
 */
class HORDESHOOTER_API FloorGenerator
{
public:
	void Generate(
		const TArray<FGridCell>* PreviousFloor, 
		FVector2D FloorDimensions, 
		TArray<FGridCell>& OutFloor);
	
private:
	void SetWalls();
};
