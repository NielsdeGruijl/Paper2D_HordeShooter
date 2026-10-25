// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePaperEnemy.generated.h"

class UEnemyWeaponController;
class UWeaponData;
class UCapsuleComponent;
class UPaperFlipbookComponent;
class UFloatingPawnMovement;
class UPaperZDAnimationComponent;
class UHealthManager;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFlashDamage, float, Duration);

UCLASS()
class HORDESHOOTER_API ABasePaperEnemy : public APawn
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FFlashDamage OnFlashDamage;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxMoveSpeed = 500;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UWeaponData* WeaponData;
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* AttackOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debugging")
	TObjectPtr<APawn> DebugTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debugging")
	bool bDebugWeaponController = false;
	
	
protected:
	UPROPERTY()
	UEnemyWeaponController* WeaponController;
	
	UPROPERTY()
	TObjectPtr<APawn> PreviousTarget;
	
	UPROPERTY()
	TObjectPtr<APawn> CurrentTarget;
	
	bool bIsFlipped = false;
	
	bool bCanAttack = true;
	
	float CurrentAbilityIndex = 0;
	
public:
	ABasePaperEnemy();
	
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	
	UEnemyWeaponController* GetWeapon() const;
	
	UFUNCTION(BlueprintCallable)
	void FlipSprite(int Direction);
	
	virtual void Attack(int AbilityIndex);
	
	virtual void ExecuteAttackAction();
	
	virtual void PullAggro(APawn* NewTarget);
	
	TObjectPtr<APawn> GetTarget();
	
	virtual void Death();
};
