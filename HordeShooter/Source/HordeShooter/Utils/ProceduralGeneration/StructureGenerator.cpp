// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureGenerator.h"

#include "FloorGenerator.h"

UStructureGenerator::UStructureGenerator()
{
}

void UStructureGenerator::Generate(const FStructureParameters& StructureParameters)
{
	int Width = StructureParameters.StructureDimensions.X;
	int Depth = StructureParameters.StructureDimensions.Y;
	
	GenerateFloor(FVector2D(Width, Depth));
	
	/*for (int32 i = 0; i < Cells.Num(); i++)
	{
		// Eastern wall
		if (i - Width < 0)
		{
			Cells[i].BlockPlacementInstructions.Add(
		        FBlockPlacement(&StructureParameters.Walls[0],
		        	FRotator(0, 90, 0)));
		}
		
		// Western wall
		if (i + Width >= Cells.Num())
		{
			Cells[i].BlockPlacementInstructions.Add(
				FBlockPlacement(&StructureParameters.Walls[0],
					FRotator(0, -90, 0)));
		}
		
		// Southern wall
		if (i % Width == 0)
		{
			Cells[i].BlockPlacementInstructions.Add(
				FBlockPlacement(&StructureParameters.Walls[0],
					FRotator(0, 180, 0)));
		}
		
		// Northern wall
		if ((i + 1) % Width == 0)
		{
			Cells[i].BlockPlacementInstructions.Add(
				FBlockPlacement(&StructureParameters.Walls[0]));
		}
	}*/
}

void UStructureGenerator::GenerateFloor(FVector2D FloorPlan)
{
	// Create new Floor
	Floors.Add(TArray<FGridCell>());
	
	TArray<FGridCell>* PreviousFloor;
	
	if (CurrentFloor == 0)
		PreviousFloor = nullptr;
	else
		PreviousFloor = &Floors[CurrentFloor - 1];
	
	// Populate floor
	FloorGenerator.Generate(PreviousFloor, FloorPlan, Floors[CurrentFloor]);
	CurrentFloor++;
}