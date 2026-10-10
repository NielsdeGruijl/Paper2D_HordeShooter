// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	FStructureParameters StructureParameters;

private:
	UPROPERTY(EditAnywhere)
	UStructureGenerator* StructureGenerator = nullptr;
	
	UPROPERTY()
	TMap<TObjectPtr<UStaticMesh>, TObjectPtr<UInstancedStaticMeshComponent>> MeshComponents;
	
public:	
	virtual void BeginPlay() override;
	
private:
	void PlaceWall(const FGridCell& Cell);
	
	UInstancedStaticMeshComponent* GetOrCreateISMC(UStaticMesh* Mesh);
};
