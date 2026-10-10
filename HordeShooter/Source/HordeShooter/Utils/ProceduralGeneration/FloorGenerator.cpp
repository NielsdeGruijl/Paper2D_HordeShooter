// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorGenerator.h"

#include "StructureGenerator.h"

void FloorGenerator::Generate(
	const TArray<FGridCell>* PreviousFloor, 
	FVector2D FloorDimensions,
	TArray<FGridCell>& OutFloor)
{
	if (!PreviousFloor)
	{
		int Width = FloorDimensions.X;
		int Depth = FloorDimensions.Y;
		
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Depth; y++)
			{
				FGridCell Cell;
				Cell.Type = CellType::Wall;
				Cell.GridPosition = FVector2D(x, y);
				
				OutFloor.Add(Cell);
			}
		}
		
		enum CardinalDirections
		{
			North = 0,
			East = 1,
			South = 2,
			West = 3
		};
		
		for (int32 i = 0; i < OutFloor.Num(); i++)
		{
			// Northern wall
			if ((i + 1) % Width == 0)
			{
				OutFloor[i].WallSlots[North] = true;
			}
			
			// Eastern wall
			if (i - Width < 0)
			{
				OutFloor[i].WallSlots[East] = true;
			}
			
			// Southern wall
			if (i % Width == 0)
			{
				OutFloor[i].WallSlots[South] = true;
			}
		
			// Western wall
			if (i + Width >= OutFloor.Num())
			{
				OutFloor[i].WallSlots[West] = true;
			}
		}
	}
	
	/*for (int32 i = 0; i < PreviousFloor->Num(); i++)
	{
		FGridCell Cell;
		Cell.GridPosition = (*PreviousFloor)[i].GridPosition;
		
		if ((*PreviousFloor)[i].Type != CellType::Wall)
		{
			Cell.Type = CellType::Empty;
			OutFloor.Add(Cell);
			continue;
		}
		
		
	}*/
}
