// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperEnemy.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"

ABasePaperEnemy::ABasePaperEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = Capsule;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");
	AnimationComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>("AnimationComponent");
	Health = CreateDefaultSubobject<UHealthManager>("Health");
	
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	Sprite->SetupAttachment(RootComponent);
	
	AnimationComponent->InitRenderComponent(Sprite);
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABasePaperEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (AnimationComponent && Sprite)
	{
		AnimationComponent->InitRenderComponent(Sprite);
	}
}

void ABasePaperEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MovementComponent->MaxSpeed = MaxMoveSpeed;
}

void ABasePaperEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ABasePaperEnemy::GetIsWalking()
{
	return MovementComponent->Velocity.Length() > 0;
}

void ABasePaperEnemy::FlipSprite(int Direction)
{
	GetController()->SetControlRotation(FRotator(0, 0, 180.0f * Direction));
}

void ABasePaperEnemy::Idle()
{
}

void ABasePaperEnemy::MoveTo(AActor* TargetActor)
{
	FVector TargetDirection = TargetActor->GetActorLocation() - GetActorLocation();
	
	TargetDirection.Normalize();
	
	AddMovementInput(TargetDirection);
}

void ABasePaperEnemy::Attack(APawn* Target)
{
	if (!AnimationComponent->GetOrCreateAnimInstance())
	{
		UE_LOG(LogTemp, Error, TEXT("NO ANIMATION INSTANCE"));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Attack!"));
	
	float direction = Target->GetActorLocation().X - GetActorLocation().X;
	
	if (direction < 0)
		FlipSprite(-1);
	else
		FlipSprite(1);		
	
	AnimationComponent->GetAnimInstance()->JumpToNode("Attack");
}
