// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthManager.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORDESHOOTER_API UHealthManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthManager();
	
	FOnHealthChanged OnHealthChanged;
	FOnDeath OnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthManager")
	float MaxHealth = 1;
	
	UPROPERTY()
	float CurrentHealth = 1;
	
private:
	UPROPERTY(EditAnywhere)
	float DestructionTime = 0.1f;
	
	UPROPERTY()
	FTimerHandle DestructionTimer;
	
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float DamageAmount);
	
	void DelayedDestruction();
};
