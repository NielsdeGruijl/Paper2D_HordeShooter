// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HORDESHOOTER_API MouseInput
{
public:
	MouseInput();
	~MouseInput();
	
public:
	static FVector GetMousePosition(UWorld* World);
};
