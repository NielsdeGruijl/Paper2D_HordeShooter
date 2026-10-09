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
	
	Health->OnDeath.AddUObject(this, &ABasePaperEnemy::Death);
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
	float Roll = 30;
	
	if (Direction > 0)
		Roll *= -1;
	
	Sprite->SetRelativeRotation(FRotator(0, 180.0f * Direction, Roll));
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
	
	if (!TargetToAttack || TargetToAttack != Target)
		TargetToAttack = Target;
	
	float direction = Target->GetActorLocation().X - GetActorLocation().X;
	
	if (direction < 0)
		FlipSprite(0);
	else
		FlipSprite(1);	
	
	AnimationComponent->GetAnimInstance()->JumpToNode("Attack");
}

void ABasePaperEnemy::ExecuteAttackAction()
{
		
}

void ABasePaperEnemy::Death()
{
}
