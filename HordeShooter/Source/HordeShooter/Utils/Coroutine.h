#pragma once

#include "CoreMinimal.h"
#include "CoroutineManager.h"

/**
 * 
 */
class HORDESHOOTER_API Coroutine
{
private:
	CoroutineUpdate* UpdateCallback = nullptr;
	CoroutineComplete* CompleteCallback = nullptr;
	
	float Duration = 0;
	float TimeElapsed = 0;
	
	bool bIsRunning = false;
	
public:
	Coroutine();
	~Coroutine();
	
	void Start(float pDuration, CoroutineUpdate* pUpdateCallback, CoroutineComplete* pCompleteCallback);
	
	bool Update(float pDeltaTime);
	
	void Complete();
};
