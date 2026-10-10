// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloorGenerator.h"
#include "StructureParameters.h"
#include "UObject/Object.h"
#include "StructureGenerator.generated.h"

UENUM()
enum class CellType : uint8
{
	Empty,
	HalfEmpty,
	Roof,
	Wall
};

USTRUCT()
struct HORDESHOOTER_API FGridCell
{
	GENERATED_BODY()
	
	CellType Type;
	
	FVector2D GridPosition;
	
	// Occupied wall slots, organized as North - East - South - West
	TArray<bool> WallSlots {false, false, false, false};
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
	
	void Generate(const FStructureParameters& StructureParameters);
	
	void GenerateFloor(FVector2D FloorPlan);
};
