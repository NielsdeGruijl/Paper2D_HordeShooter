// Fill out your copyright notice in the Description page of Project Settings.


#include "SpriteVFXActor.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

ASpriteVFXActor::ASpriteVFXActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	Flipbook->SetupAttachment(RootComponent);
	
	Flipbook->SetLooping(false);
}

void ASpriteVFXActor::BeginPlay()
{
	Super::BeginPlay();
	
	Flipbook->SetLooping(false);
	
	Flipbook->PlayFromStart();
	
	float TotalDuration = Flipbook->GetFlipbook()->GetTotalDuration();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &ASpriteVFXActor::DestroyVFX, TotalDuration);
}

void ASpriteVFXActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpriteVFXActor::DestroyVFX()
{
	Destroy();
}

