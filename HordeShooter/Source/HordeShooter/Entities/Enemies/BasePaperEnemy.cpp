// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperEnemy.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"
#include "Engine/CollisionProfile.h"
#include "HordeShooter/EnemyWeaponController.h"

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
	
	AttackOrigin = CreateDefaultSubobject<USceneComponent>("AttackOrigin");
	AttackOrigin->SetupAttachment(Sprite);
	
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
	
	WeaponController = NewObject<UEnemyWeaponController>(this);
}

void ABasePaperEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Health->OnDeath.AddUObject(this, &ABasePaperEnemy::Death);
	
	Health->OnHealthChanged.AddLambda([this](float Health)
	{
		OnFlashDamage.Broadcast(0.2f);
	});
	
	if (WeaponController)
	{
		WeaponController->OwningPawn = this;
		WeaponController->Initialize(WeaponData);
	}
	
	WeaponController->bIsDebugging = &bDebugWeaponController;
}
		
void ABasePaperEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	WeaponController->Update(DeltaSeconds);
	
	if (MovementComponent->Velocity.X > 0 && !bIsFlipped)
		FlipSprite(0);
	else if (MovementComponent->Velocity.X < 0 && !bIsFlipped)
		FlipSprite(1);
}

UEnemyWeaponController* ABasePaperEnemy::GetWeapon() const
{
	if (!WeaponController)
		return nullptr;
	
	return WeaponController;
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

void ABasePaperEnemy::Attack(int AbilityIndex, APawn* Target)
{
	WeaponController->CurrentPlan.bIsExecuting = true;
	
	if (!AnimationComponent->GetOrCreateAnimInstance())
	{
		UE_LOG(LogTemp, Error, TEXT("NO ANIMATION INSTANCE"));
		return;
	}
	
	CurrentAbilityIndex = AbilityIndex;
	
	if (WeaponController && !WeaponController->CanStartAbility(AbilityIndex))
		return;
	
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
	if (!WeaponController)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon controller is nullptr"));
		return;
	}
	
	WeaponController->StartAbility(CurrentAbilityIndex, AttackOrigin->GetComponentLocation(), TargetToAttack->GetActorLocation());
}

void ABasePaperEnemy::Death()
{
	Destroy();
}
