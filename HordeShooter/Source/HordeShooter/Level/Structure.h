// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HordeShooter/Utils/ProceduralGeneration/StructureGenerator.h"
#include "HordeShooter/Utils/ProceduralGeneration/StructureParameters.h"
#include "Structure.generated.h"

struct FGridCell;
class UStructureGenerator;

UCLASS()
class HORDESHOOTER_API AStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	AStructure();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStructureStyle> Style;

private:
	UPROPERTY(EditAnywhere)
	UStructureGenerator* StructureGenerator = nullptr;
	
	UPROPERTY()
	TMap<TObjectPtr<UStaticMesh>, TObjectPtr<UInstancedStaticMeshComponent>> MeshComponents;

	FRandomStream RandomStream;
	
public:	
	virtual void BeginPlay() override;
	
private:
	TSoftObjectPtr<UStaticMesh> GetRandomMesh(ECellType MeshTag, ECellSubType SubType);
	
	void PlaceWall(const FGridCell& Cell, int FloorNumber);
	
	//void PlaceRoof(const FGridCell& Cell, int FloorNumber);
	
	UInstancedStaticMeshComponent* GetOrCreateISMC(UStaticMesh* Mesh);
};
