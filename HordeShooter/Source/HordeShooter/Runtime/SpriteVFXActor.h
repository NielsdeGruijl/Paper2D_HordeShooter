// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpriteVFXActor.generated.h"

class UPaperFlipbookComponent;

UCLASS()
class HORDESHOOTER_API ASpriteVFXActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASpriteVFXActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPaperFlipbookComponent* Flipbook;
	
private:
	FTimerHandle TimerHandle;
	
protected:
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
private:
	void DestroyVFX();
};
