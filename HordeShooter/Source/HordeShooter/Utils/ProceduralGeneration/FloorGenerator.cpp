// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorGenerator.h"

#include "IPropertyTable.h"
#include "NiagaraRibbonRendererProperties.h"
#include "StructureGenerator.h"
#include "StructureParameters.h"
#include "VerseVM/VVMValuePrinting.h"

void FloorGenerator::Generate(
	const TArray<FGridCell>* PreviousFloor, 
	FVector FloorDimensions,
	TArray<FGridCell>& OutFloor,
	float GenerateRoofsCoeff)
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
				Cell.Type = ECellType::Wall;
				Cell.GridPosition = FVector2D(x, y);
				
				OutFloor.Add(Cell);
			}
		}
		
		SetNeighbours(OutFloor, FloorDimensions.Y);
		
		return;
	}
	
	int GridSize = PreviousFloor->Num();
	
	for (int32 i = 0; i < GridSize; i++)
	{
		FGridCell Cell;
		Cell.GridPosition = (*PreviousFloor)[i].GridPosition;
		
		if ((*PreviousFloor)[i].Type != ECellType::Wall)
		{
			Cell.Type = ECellType::Empty;
			OutFloor.Add(Cell);
			continue;
		}
		
		Cell.Type = ECellType::Wall;
		OutFloor.Add(Cell);
	}
	
	SetNeighbours(OutFloor, FloorDimensions.Y);
	
	// Loop over cells by column
	for (int x = 0; x < GridSize; x += FloorDimensions.Y)
	{
		bool bRoofColumn = false;
		bool bFirstCorner = true;
		
		for (int y = 0; y < FloorDimensions.Y; y++)
		{
			if (OutFloor[x + y].Type == ECellType::Empty)
				continue;
			
			// Each cell is already a wall by default
			if (!bFirstCorner && !bRoofColumn)
				continue;
			
			if (bRoofColumn && !OutFloor[x + y].IsCorner() && !OutFloor[x + y].IsCorridorEnd())
			{
				OutFloor[x + y].Type = ECellType::Roof;
				
				if (OutFloor[x + y].IsCorridor())
					OutFloor[x + y].SubType = ECellSubType::Corridor;
				
				if (OutFloor[x + y].IsSideEmpty(ECellSide::East))
				{
					OutFloor[x + y].EmptyNeighbours = 0;
					OutFloor[x + y].SetSide(ECellSide::North, true);
				}
				else if (OutFloor[x + y].IsSideEmpty(ECellSide::West))
				{
					OutFloor[x + y].EmptyNeighbours = 0;
					OutFloor[x + y].SetSide(ECellSide::South, true);
				}
				
				continue;
			}
			
			if (OutFloor[x + y].IsCorner() || OutFloor[x + y].IsCorridorEnd())
			{
				if (bRoofColumn)
				{
					SetRoofCorner(OutFloor[x + y]);
					continue;
				}
				
				if (bFirstCorner)
				{
					bFirstCorner = false;
				
					int RoofWeight = 5;
					int WallWeight = 5 * GenerateRoofsCoeff;
				
					UE_LOG(LogTemp, Log, TEXT("WallWeight = %d"), WallWeight);
				
					int TotalWeight = RoofWeight + WallWeight;
				
					double chance = FMath::RandRange(0, TotalWeight);
				
					if (chance <= RoofWeight)
					{
						SetRoofCorner(OutFloor[x + y]);
					
						bRoofColumn = true;
					}
				}
			}
		}
	}
}

void FloorGenerator::SetRoofCorner(FGridCell& Cell)
{
	Cell.Type = ECellType::RoofCorner;
					
	if (Cell.IsSideEmpty(ECellSide::East) && Cell.IsSideEmpty(ECellSide::West))
	{
		Cell.SubType = ECellSubType::Corridor;
						
		if (Cell.IsSideEmpty(ECellSide::North))
		{
			Cell.EmptyNeighbours = 0;
			Cell.SetSide(ECellSide::South, true);
		}
		else if (Cell.IsSideEmpty(ECellSide::South))
		{
			Cell.EmptyNeighbours = 0;
			Cell.SetSide(ECellSide::North, true);
		}
	}
	else if (Cell.IsSideEmpty(ECellSide::East))
	{
		Cell.EmptyNeighbours = 0;
		Cell.SetSide(ECellSide::North, true);
	}
	else if (Cell.IsSideEmpty(ECellSide::West))
	{
		Cell.EmptyNeighbours = 0;
		Cell.SetSide(ECellSide::South, true);
	}
}

void FloorGenerator::SetNeighbours(TArray<FGridCell>& Floor, int FloorDepth)
{
	for (int32 i = 0; i < Floor.Num(); i++)
	{
		if (Floor[i].Type == ECellType::Empty)
			continue;
		
		// Northern wall
		if ((i + 1) % FloorDepth == 0 || 
			Floor[i + 1].Type == ECellType::Empty)
		{
			Floor[i].EmptyNeighbours |= (uint8)ECellSide::North;
		}
		
		// Eastern wall
		if (i - FloorDepth < 0 || 
			Floor[i - FloorDepth].Type == ECellType::Empty)
		{
			Floor[i].EmptyNeighbours |= (uint8)ECellSide::East;
		}
		
		// Southern wall
		if (i % FloorDepth == 0 || 
			(i - 1 > 0 && Floor[i - 1].Type == ECellType::Empty))
		{
			Floor[i].EmptyNeighbours |= (uint8)ECellSide::South;
		}
		
		// Western wall
		if (i + FloorDepth >= Floor.Num() ||
			Floor[i + FloorDepth].Type == ECellType::Empty)
		{
			Floor[i].EmptyNeighbours |= (uint8)ECellSide::West;
		}
	}
}
