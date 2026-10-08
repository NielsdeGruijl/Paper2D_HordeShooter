// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"

APlayerActionController::APlayerActionController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerActionController::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryWeapon = NewObject<UPlayerWeaponController>(this);
	
	PrimaryWeapon->OwningPawn = this;
	PrimaryWeapon->SetWeapon(PrimaryWeaponData);
	
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void APlayerActionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerActionController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!InputMappingContext)
		return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(Cast<APlayerController>(GetController())->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerActionController::Move);
		
		Input->BindAction(PrimaryAbilityAction, ETriggerEvent::Started, this, &APlayerActionController::StartPrimaryAbility);
		Input->BindAction(PrimaryAbilityAction, ETriggerEvent::Completed, this, &APlayerActionController::StopPrimaryAbility);
		
		Input->BindAction(SecondaryAbilityAction, ETriggerEvent::Started, this, &APlayerActionController::StartSecondaryAbility);
		Input->BindAction(SecondaryAbilityAction, ETriggerEvent::Completed, this, &APlayerActionController::StopSecondaryAbility);
	}
}

void APlayerActionController::StartPrimaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StartPrimary();
}

void APlayerActionController::StopPrimaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StopPrimary();
}

void APlayerActionController::StartSecondaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StartSecondary();
}

void APlayerActionController::StopSecondaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StopSecondary();
}

void APlayerActionController::Move(const FInputActionValue& Value)
{
	FVector2D MovementInput = Value.Get<FVector2D>();
	
	MovementInput.Normalize();
	
	AddMovementInput(FVector(MovementInput.X, MovementInput.Y, 0), 1 , false);
}

