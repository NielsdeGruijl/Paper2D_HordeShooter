// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerWeaponController.h"
#include "GameFramework/Character.h"
#include "PlayerActionController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class HORDESHOOTER_API APlayerActionController : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerActionController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EDitAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* PrimaryAbilityAction;
	
	UPROPERTY(EDitAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SecondaryAbilityAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UWeaponData* PrimaryWeaponData;
	
private:
	UPROPERTY()
	UPlayerWeaponController* PrimaryWeapon;
	
protected:
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void StartPrimaryAbility(const FInputActionValue& Value);
	void StopPrimaryAbility(const FInputActionValue& Value);
	
	void StartSecondaryAbility(const FInputActionValue& Value);
	void StopSecondaryAbility(const FInputActionValue& Value);

};
