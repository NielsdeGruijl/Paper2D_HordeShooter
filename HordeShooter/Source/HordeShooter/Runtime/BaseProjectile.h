// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class HORDESHOOTER_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 2000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gravity = 1;
	
	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;
	
public:	
	ABaseProjectile();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
