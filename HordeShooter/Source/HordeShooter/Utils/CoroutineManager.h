// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subsystems/WorldSubsystem.h"
#include "CoroutineManager.generated.h"

DECLARE_DELEGATE_OneParam(CoroutineUpdate, float TimeElapsed);
DECLARE_DELEGATE(CoroutineComplete);

class Coroutine;

UCLASS()
class HORDESHOOTER_API UCoroutineManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:	
	
private:
	TArray<TSharedPtr<Coroutine>> ActiveCoroutines;
	
	TArray<TSharedPtr<Coroutine>> InactiveCoroutines;
	
	TArray<TSharedPtr<Coroutine>> CoroutinesToDeactivate;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override;
	
	TWeakPtr<Coroutine> StartCoroutine(float Duration, CoroutineUpdate* updateCallback, CoroutineComplete* completeCallback);
	
	void StopCoroutine(TWeakPtr<Coroutine> Coroutine);
	
private:
	void DeactivateCoroutines();
	
	
};
