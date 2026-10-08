// Fill out your copyright notice in the Description page of Project Settings.


#include "CoroutineManager.h"
#include "Coroutine.h"
#include "Stats/Stats.h"

void UCoroutineManager::DeactivateCoroutines()
{
	for (TSharedPtr Coroutine : CoroutinesToDeactivate)
	{
		InactiveCoroutines.Add(Coroutine);
		ActiveCoroutines.Remove(Coroutine);
	}
	
	CoroutinesToDeactivate.Empty();
}

void UCoroutineManager::Tick(float DeltaTime)
{
	for (TSharedPtr Coroutine : ActiveCoroutines)
	{
		if (Coroutine->Update(DeltaTime))
			CoroutinesToDeactivate.Add(Coroutine);
	}
	
	if (!CoroutinesToDeactivate.IsEmpty())
		DeactivateCoroutines();
}

TStatId UCoroutineManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UCoroutineManager, STATGROUP_Tickables);
}

TWeakPtr<Coroutine> UCoroutineManager::StartCoroutine(float pDuration, CoroutineUpdate* pUpdateCallback, CoroutineComplete* pFinishedCallback)
{
	if (InactiveCoroutines.IsEmpty())
	{	
		TSharedPtr<Coroutine> NewCoroutine = MakeShared<Coroutine>();
		ActiveCoroutines.Add(NewCoroutine);
		NewCoroutine->Start(pDuration, pUpdateCallback, pFinishedCallback);
		return NewCoroutine;
	}
	
	TSharedPtr<Coroutine> Coroutine = InactiveCoroutines[0];
	ActiveCoroutines.Add(Coroutine);
	InactiveCoroutines.Remove(Coroutine);
	Coroutine->Start(pDuration, pUpdateCallback, pFinishedCallback);
	return Coroutine;
}

void UCoroutineManager::StopCoroutine(TWeakPtr<Coroutine> Coroutine)
{
	if (!Coroutine.IsValid())
		return;
	
	CoroutinesToDeactivate.Add(Coroutine.Pin());
}

