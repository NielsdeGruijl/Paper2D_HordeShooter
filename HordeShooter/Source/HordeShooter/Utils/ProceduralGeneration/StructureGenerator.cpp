// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureGenerator.h"

UStructureGenerator::UStructureGenerator()
{
}

void UStructureGenerator::Generate(FVector StructureDimensions)
{
	int Width = StructureDimensions.X;
	int Depth = StructureDimensions.Y;
	
	for (int i = 0; i < StructureDimensions.Z; i++)
	{
		GenerateFloor(StructureDimensions);
	}
}

void UStructureGenerator::GenerateFloor(FVector FloorPlan)
{
	TArray<FGridCell>* PreviousFloor;
	
	if (CurrentFloor == 0)
		PreviousFloor = nullptr;
	else
		PreviousFloor = &Floors[CurrentFloor - 1];
	
	// Create new Floor
	Floors.Add(TArray<FGridCell>());
	
	double ShortestRoofWidth = FMath::Min(FloorPlan.X, FloorPlan.Y);
	int MinRoofHeight = FMath::CeilToInt(ShortestRoofWidth * 0.5f); 
	int MaxRoofFloor = FloorPlan.Z - MinRoofHeight;
	
	float GenerateRoofCoeff = FMath::Max(0, 1 - (float)CurrentFloor / (float)MaxRoofFloor);
	
	// Populate floor
	FloorGenerator.Generate(PreviousFloor, FloorPlan, Floors[CurrentFloor], GenerateRoofCoeff);
	CurrentFloor++;
}