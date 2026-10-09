// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnDirector.generated.h"

UCLASS()
class HORDESHOOTER_API AEnemySpawnDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawnDirector();

public:	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

};
