// Fill out your copyright notice in the Description page of Project Settings.


#include "Structure.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "HordeShooter/Utils/ProceduralGeneration/StructureGenerator.h"


// Sets default values
AStructure::AStructure()
{
	PrimaryActorTick.bCanEverTick = true;

	StructureGenerator = CreateDefaultSubobject<UStructureGenerator>("StructureGenerator");
}

void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
	StructureGenerator->Generate(StructureParameters);
	
	for (TArray<FGridCell> Floor : StructureGenerator->Floors)
	{
		for (FGridCell Cell : Floor)
		{
			switch (Cell.Type)
			{
			case (CellType::Wall):
				PlaceWall(Cell);
				break;
			case (CellType::Empty):
				break;
			case (CellType::HalfEmpty):
				break;
			case (CellType::Roof):
				break;
			default:
				break;
			}
		}
	}
}


void AStructure::PlaceWall(const FGridCell& Cell)
{
	for (int32 i = 0; i < Cell.WallSlots.Num(); i++)
	{
		bool bShouldPlaceWall = Cell.WallSlots[i];
		
		if (!bShouldPlaceWall)
			continue;
		
		UStaticMesh* Mesh = StructureParameters.Walls[0].LoadSynchronous();
		
		if (!Mesh)
		{
			UE_LOG(LogTemp, Error, TEXT("NO MESH LOADED"));
			continue;
		}
		
		UE_LOG(LogTemp, Log, TEXT("Place wall %i"), i);
		
		UInstancedStaticMeshComponent* ISMC = GetOrCreateISMC(Mesh);
		FVector Position = FVector(Cell.GridPosition.X, Cell.GridPosition.Y, 0);
		
		Position *= 400; // TODO: Remove magic number!!!!
		
		FRotator Direction = FRotator(0, 90 * i, 0);
		
		Position += Direction.RotateVector(FVector(0, 50, 0)) * 4;
			
		const FTransform Transform(
			Direction, 
			Position, 
			FVector(4, 1, 4));
			
		ISMC->AddInstance(Transform, false);
	}
}

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


