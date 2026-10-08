// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePaperEnemy.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;
class UFloatingPawnMovement;
class UPaperZDAnimationComponent;
class UHealthManager;
/**
 * 
 */
UCLASS()
class HORDESHOOTER_API ABasePaperEnemy : public APawn
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed = 500;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackDamage = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* Capsule;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperFlipbookComponent* Sprite;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperZDAnimationComponent* AnimationComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthManager* Health;
	
public:
	ABasePaperEnemy();
	
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	
	UFUNCTION(BlueprintCallable)
	bool GetIsWalking();
	
	UFUNCTION(BlueprintCallable)
	void FlipSprite(int Direction);
	
	virtual void Idle();
	
	virtual void MoveTo(AActor* TargetActor);
	
	virtual void Attack(APawn* Target);
	
	virtual void ExecuteAttackAction();
	
	virtual void Death();
};
