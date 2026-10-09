// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaperCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "HordeShooter/PlayerWeaponController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"

APlayerPaperCharacter::APlayerPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryWeapon = NewObject<UPlayerWeaponController>(this);
	
	PrimaryWeapon->OwningPawn = this;
	if (PrimaryWeaponData)
		PrimaryWeapon->SetWeapon(PrimaryWeaponData);
	else
		UE_LOG(LogTemp, Error, TEXT("NO PRIMARY WEAPON DATA FOUND"));
	
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void APlayerPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaperCharacter::Move);
		
		Input->BindAction(PrimaryAbilityAction, ETriggerEvent::Started, this, &APlayerPaperCharacter::StartPrimaryAbility);
		Input->BindAction(PrimaryAbilityAction, ETriggerEvent::Completed, this, &APlayerPaperCharacter::StopPrimaryAbility);
		
		Input->BindAction(SecondaryAbilityAction, ETriggerEvent::Started, this, &APlayerPaperCharacter::StartSecondaryAbility);
		Input->BindAction(SecondaryAbilityAction, ETriggerEvent::Completed, this, &APlayerPaperCharacter::StopSecondaryAbility);
	}
}

void APlayerPaperCharacter::StartPrimaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StartPrimary();
}

void APlayerPaperCharacter::StopPrimaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StopPrimary();
}

void APlayerPaperCharacter::StartSecondaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StartSecondary();
}

void APlayerPaperCharacter::StopSecondaryAbility(const FInputActionValue& Value)
{
	PrimaryWeapon->StopSecondary();
}

void APlayerPaperCharacter::FlipSprite(const int Direction)
{
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f * Direction, 0.0f));
}

void APlayerPaperCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementInput = Value.Get<FVector2D>();
	
	MovementInput.Normalize();
	
	if (MovementInput.X > 0)
		FlipSprite(1);
	else if (MovementInput.X < 0)
		FlipSprite(0);
	
	AddMovementInput(FVector(MovementInput.X, MovementInput.Y, 0), 1 , false);
}
