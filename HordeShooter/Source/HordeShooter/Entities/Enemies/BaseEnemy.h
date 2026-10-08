// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseEnemy.generated.h"

class UPaperFlipbookComponent;
class UPaperFlipbook;
class UHealthManager;
class UFloatingPawnMovement;

UENUM(BlueprintType)
enum class EEnemyAnimation : uint8
{
	Idle,
	Walk,
	Attack
};

UCLASS()
class HORDESHOOTER_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();
	
	UPROPERTY(EditAnywhere, Category = Movement)
	float MaxMoveSpeed;
	
	UPROPERTY(EditAnywhere)
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthManager* Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* FlipbookComponent;
	
	UPROPERTY(EditAnywhere, Category = "Animations")
	TMap<EEnemyAnimation, UPaperFlipbook*> Animations;
	
private:
	UPROPERTY()
	EEnemyAnimation currentAnimation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void PlayAnimation(EEnemyAnimation Animation);
	
	void PerformAttack();
};