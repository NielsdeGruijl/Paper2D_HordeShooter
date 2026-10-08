// Fill out your copyright notice in the Description page of Project Settings.


#include "Coroutine.h"

Coroutine::Coroutine()
{
}

Coroutine::~Coroutine()
{
}

void Coroutine::Start(float pDuration, CoroutineUpdate* pUpdateCallback, CoroutineComplete* pCompleteCallback)
{
	Duration = pDuration;
	UpdateCallback = pUpdateCallback;
	CompleteCallback = pCompleteCallback;
	
	TimeElapsed = 0;
	bIsRunning = true;
}

bool Coroutine::Update(float pDeltaTime)
{
	if (!bIsRunning)
		return true;
	
	if (TimeElapsed >= Duration)
	{
		Complete();
		return true;
	}
	
	TimeElapsed += pDeltaTime;
	UpdateCallback->Execute(TimeElapsed);
	
	return false;
}

void Coroutine::Complete()
{
	CompleteCallback->Execute();
	
	TimeElapsed = 0;
	Duration = 0;
	
	bIsRunning = false;
	
	UpdateCallback = nullptr;
	CompleteCallback = nullptr;
}
