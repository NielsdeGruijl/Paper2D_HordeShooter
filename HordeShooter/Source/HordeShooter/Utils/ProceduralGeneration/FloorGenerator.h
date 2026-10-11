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
		FVector FloorDimensions, 
		TArray<FGridCell>& OutFloor, 
		float GenerateRoofsCoeff);
	
private:
	void SetRoofCorner(FGridCell& Cell);
	
	void SetNeighbours(TArray<FGridCell>& Floor, int FloorDepth);
};
