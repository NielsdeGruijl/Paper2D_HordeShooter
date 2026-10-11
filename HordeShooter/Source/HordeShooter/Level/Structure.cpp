// Fill out your copyright notice in the Description page of Project Settings.


#include "Structure.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "HordeShooter/Utils/ProceduralGeneration/StructureGenerator.h"


// Sets default values
AStructure::AStructure()
{
	PrimaryActorTick.bCanEverTick = true;

	StructureGenerator = CreateDefaultSubobject<UStructureGenerator>("StructureGenerator");
	
	int Seed = FMath::Rand();
	
	RandomStream.Initialize(Seed);
	
	UE_LOG(LogTemp, Log, TEXT("Seed: %i"), Seed);
}

void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
	StructureGenerator->Generate(Style->StructureDimensions);
	
	for (int32 i = 0; i < StructureGenerator->Floors.Num(); i++)
	{
		for (FGridCell Cell : StructureGenerator->Floors[i])
		{
			PlaceWall(Cell, i);
		}
	}
}

TSoftObjectPtr<UStaticMesh> AStructure::GetRandomMesh(ECellType MeshTag, ECellSubType SubType)
{
	if (!Style->MeshPieces.Contains(MeshTag))
	{
		UE_LOG(LogTemp, Error, TEXT("NO MESH CATEGORY WITH TYPE %s FOUND"), *UEnum::GetValueAsString(MeshTag));
		return nullptr;
	}
	
	TArray<FMeshPiece> Meshes = Style->MeshPieces.Find(MeshTag)->MeshPieces;
	
	TArray<FMeshPiece> Candidates;
	
	for (FMeshPiece MeshPiece : Meshes)
	{
		if (MeshPiece.SubType == SubType)
			Candidates.Add(MeshPiece);
	}
	
	if (Candidates.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NO MESH CANDIDATE WITH SUBTYPE %s FOUND"), *UEnum::GetValueAsString(SubType));
		return nullptr;
	}

	float TotalWeight = 0;
		
	for (int32 i = 0; i < Candidates.Num(); i++)
	{
		TotalWeight += Candidates[i].Weight;
	}
	
	float ChosenWeight = RandomStream.FRandRange(0, TotalWeight);
	
	float CurrentWeight = 0;
	
	for (int32 i = 0; i < Candidates.Num(); i++)
	{
		CurrentWeight += Candidates[i].Weight;
		
		if (ChosenWeight <= CurrentWeight)
		{
			return Candidates[i].Mesh;
		}
	}
	
	// If no random mesh was selected, return first mesh in array
	return Candidates[0].Mesh;
}


void AStructure::PlaceWall(const FGridCell& Cell, int FloorNumber)
{
	static const ECellSide Sides[4] = {
		ECellSide::North, ECellSide::East, ECellSide::South, ECellSide::West
	};
	
	for (int i = 0; i < 4; i++)
	{
		if (!Cell.IsSideEmpty(Sides[i]))
			continue;
		
		TSoftObjectPtr<UStaticMesh> SoftMesh = GetRandomMesh(Cell.Type, Cell.SubType);
		
		UStaticMesh* Mesh = SoftMesh.LoadSynchronous();
		
		if (!Mesh)
		{
			UE_LOG(LogTemp, Error, TEXT("NO MESH LOADED"));
			continue;
		}
		
		UE_LOG(LogTemp, Log, TEXT("Place wall %i"), i);
		
		UStaticMeshSocket* Socket = Mesh->FindSocket("Socket");
		
		UInstancedStaticMeshComponent* ISMC = GetOrCreateISMC(Mesh);
		FVector Position = FVector(Cell.GridPosition.X, Cell.GridPosition.Y, FloorNumber);
		
		Position *= 400; // TODO: Remove magic number!!!!
		
		FRotator Direction = FRotator(0, 90 * i, 0);
		
		FVector Scale = FVector::OneVector;
		
		// Yucky code ahead
		
		if (Cell.Type == ECellType::Wall)
		{
			Position += Direction.RotateVector(FVector(0, 50, 0)) * 4;
			Scale = FVector(4, 1, 4);
		}
		else
		{
			Scale = FVector(4, 4, 4);
		}

			
		const FTransform Transform(
			Direction, 
			Position, 
			Scale);
			
		ISMC->AddInstance(Transform, false);
		
		if (Cell.Type == ECellType::Roof)
			break;
	}
}

/*void AStructure::PlaceRoof(const FGridCell& Cell, int FloorNumber)
{
	TSoftObjectPtr<UStaticMesh> SoftMesh = GetRandomMesh(Cell.Type);
		
	UStaticMesh* Mesh = SoftMesh.LoadSynchronous();
		
	if (!Mesh)
	{
		UE_LOG(LogTemp, Error, TEXT("NO MESH LOADED"));
		return;
	}
		
	UInstancedStaticMeshComponent* ISMC = GetOrCreateISMC(Mesh);
	FVector Position = FVector(Cell.GridPosition.X, Cell.GridPosition.Y, FloorNumber);
		
	Position *= 400; // TODO: Remove magic number!!!
		
	FRotator Direction = FRotator(0, 0, 0);
		
	//Position += Direction.RotateVector(FVector(0, 50, 0)) * 4; // TODO: Remove magic number!!!
			
	const FTransform Transform(
		Direction, 
		Position, 
		FVector(4, 4, 4)); // TODO: Remove magic number!!!
			
	ISMC->AddInstance(Transform, false);
}*/

UInstancedStaticMeshComponent* AStructure::GetOrCreateISMC(UStaticMesh* Mesh)
{
	if (TObjectPtr<UInstancedStaticMeshComponent>* Found = MeshComponents.Find(Mesh))
	{
		return *Found;
	}
	
	UInstancedStaticMeshComponent* ISMC = NewObject<UInstancedStaticMeshComponent>(this);

	ISMC->SetStaticMesh(Mesh);
	ISMC->SetupAttachment(GetRootComponent());
	ISMC->SetMobility(EComponentMobility::Movable);
	ISMC->RegisterComponent();
	AddInstanceComponent(ISMC);
	
	MeshComponents.Add(Mesh, ISMC);
	return ISMC;
}


