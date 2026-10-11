// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureGenerator.h"
#include "Engine/DataAsset.h"
#include "StructureParameters.generated.h"

enum class ECellSubType : uint8;
enum class ECellType : uint8;


USTRUCT()
struct HORDESHOOTER_API FMeshPiece
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	ECellSubType SubType = ECellSubType::None;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> Mesh;
};

USTRUCT()
struct HORDESHOOTER_API FMeshCategory
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FMeshPiece> MeshPieces;
};

UCLASS()
class HORDESHOOTER_API UStructureStyle : public UDataAsset
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditAnywhere)
	FVector StructureDimensions;
	
	UPROPERTY(EditAnywhere)
	int CellSize = 400;
	
	UPROPERTY(EditAnywhere)
	TMap<ECellType, FMeshCategory> MeshPieces;
};