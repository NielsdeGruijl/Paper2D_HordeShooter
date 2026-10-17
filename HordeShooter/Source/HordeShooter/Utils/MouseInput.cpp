// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseInput.h"

MouseInput::MouseInput()
{
}

MouseInput::~MouseInput()
{
}

FVector MouseInput::GetMousePosition(UWorld* World)
{
	if (!World || !World->GetFirstPlayerController())
		return FVector::ZeroVector;
	
	FHitResult Hit;
	World->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Hit);
	
	if (!Hit.bBlockingHit)
		return FVector::ZeroVector;
	
	FVector Position = Hit.Location;
	
	Position = FVector(Position.X, Position.Y, Position.Z);
	
	return Position;
}
