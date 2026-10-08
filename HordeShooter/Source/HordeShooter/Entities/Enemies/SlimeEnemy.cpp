// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeEnemy.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "HordeShooter/Entities/Systems/HealthManager.h"

ASlimeEnemy::ASlimeEnemy() 
{
	AttackCollider = CreateDefaultSubobject<UBoxComponent>("AttackCollider");
	AttackCollider->SetupAttachment(Sprite);
}

void ASlimeEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Health->OnDeath.AddUObject(this, &ASlimeEnemy::Death);
}

void ASlimeEnemy::ExecuteAttackAction()
{
	Super::ExecuteAttackAction();
	
	TArray<AActor*> actors;
	AttackCollider->GetOverlappingActors(actors);
	
	for (AActor* actor : actors)
	{
		if (actor == this)
			continue;
		
		if (UHealthManager* Healthmanager = actor->GetComponentByClass<UHealthManager>())
		{
			Healthmanager->TakeDamage(AttackDamage);
		}
	}
}

void ASlimeEnemy::Death()
{
	Super::Death();
	
	Destroy();
}
