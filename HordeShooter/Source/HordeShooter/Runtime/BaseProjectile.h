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
	
	UPROPERTY(EditAnywhere)
	float PenetrationValue = 1;
	
protected:
	float ImpactDamage = 0;
	
private:
	float EntitiesPenetrated = 0;
	
	FVector GravityDirection = FVector(0, 0, -1);
	
public:
	ABaseProjectile();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Initialize(float Damage);
	
	virtual void Launch(const FVector Velocity, const FVector UpVector);
	
protected:
	virtual void OnOverlapInternal(AActor* OtherActor);
	
private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
