// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimNotify.h"
#include "PaperZDAnimNotify_Attack.generated.h"

/**
 * 
 */
UCLASS()
class HORDESHOOTER_API UPaperZDAnimNotify_Attack : public UPaperZDAnimNotify
{
	GENERATED_BODY()
	
public:
	UPaperZDAnimNotify_Attack();
	
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;
	FName GetDisplayName_Implementation() const override;
};
