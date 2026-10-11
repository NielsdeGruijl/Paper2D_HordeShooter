// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <bitset>

#include "CoreMinimal.h"
#include "FloorGenerator.h"
#include "UObject/Object.h"
#include "StructureGenerator.generated.h"

UENUM()
enum class ECellType : uint8
{
	Empty,
	Roof,
	HalfRoof,
	RoofCorner,
	Wall,
};

UENUM()
enum class ECellSubType : uint8
{
	None,
	Door,
	Corridor
};

UENUM()
enum class ECellSide : uint8
{
	None = 0,
	North = 1 << 0, // 0001
	South = 1 << 1, // 0010
	East = 1 << 2,  // 0100
	West = 1 << 3,  // 1000
};
ENUM_CLASS_FLAGS(ECellSide);

USTRUCT()
struct HORDESHOOTER_API FGridCell
{
	GENERATED_BODY()
	
	static constexpr uint8 North = 1;
	static constexpr uint8 South = 2;
	static constexpr uint8 East = 4;
	static constexpr uint8 West = 8;
	
	ECellType Type;
	
	ECellSubType SubType = ECellSubType::None;
	
	uint8 EmptyNeighbours = 0;
	
	FVector2D GridPosition;
	
	void SetSide(ECellSide side, bool bIsEmpty)
	{
		if (bIsEmpty)
			EmptyNeighbours |= (uint8)side;
		else
			EmptyNeighbours &= ~(uint8)side;
	}
	
	bool IsSideEmpty(ECellSide side) const
	{
		return (EmptyNeighbours & (uint8)side) != 0;
	}
	
	bool IsCorner() const
	{
		return EmptyNeighbours == (North | East) || EmptyNeighbours == (North | West) || 
			EmptyNeighbours == (South | East) || EmptyNeighbours == (South | West); 
	}
	
	bool IsCorridor() const
	{
		return EmptyNeighbours == (North | South) || EmptyNeighbours == (East | West);
	}
	
	bool IsCorridorEnd() const
	{
		return FMath::CountBits(EmptyNeighbours) == 3;
	}
	
	bool IsIsolated() const
	{
		return EmptyNeighbours == 0;
	}
};

UCLASS()
class HORDESHOOTER_API UStructureGenerator : public UObject
{
	GENERATED_BODY()
	
private:
	FloorGenerator FloorGenerator;
	
	UPROPERTY()
	int CurrentFloor = 0;
	
public:
	TArray<TArray<FGridCell>> Floors;
	
public:
	UStructureGenerator();
	
	void Generate(FVector StructureDimensions);
	
	void GenerateFloor(FVector StructureDimensions);
};
