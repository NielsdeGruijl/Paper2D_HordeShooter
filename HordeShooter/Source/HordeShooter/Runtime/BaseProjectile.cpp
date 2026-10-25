// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"

ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMovementComponent = 
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	
	ProjectileMovementComponent->InitialSpeed = MovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MovementSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float GravityScale = FMath::Abs(GetWorld()->GetGravityZ());
	ProjectileMovementComponent->Velocity += GravityScale * GravityDirection * DeltaTime;
}

void ABaseProjectile::Initialize(float Damage)
{
	ImpactDamage = Damage;
}

void ABaseProjectile::Launch(const FVector Velocity, const FVector UpVector)
{
	GravityDirection = -UpVector;
	ProjectileMovementComponent->Velocity = Velocity;
}

void ABaseProjectile::OnOverlapInternal(AActor* OtherActor)
{
	UHealthManager* HealthManager = OtherActor->FindComponentByClass<UHealthManager>();
	
	if (HealthManager)
		HealthManager->TakeDamage(ImpactDamage);
}

void ABaseProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (GetInstigator() && OtherActor == GetInstigator())
		return;
	
	OnOverlapInternal(OtherActor);
	
	EntitiesPenetrated++;

	if (EntitiesPenetrated >= PenetrationValue)
	{
		Destroy();
	}
}
