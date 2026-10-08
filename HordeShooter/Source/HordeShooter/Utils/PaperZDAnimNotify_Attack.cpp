// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperZDAnimNotify_Attack.h"

#include "PaperZDAnimInstance.h"
#include "HordeShooter/Entities/Enemies/BasePaperEnemy.h"

UPaperZDAnimNotify_Attack::UPaperZDAnimNotify_Attack()
{
}

void UPaperZDAnimNotify_Attack::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	Super::OnReceiveNotify_Implementation(OwningInstance);
	
	if (!OwningInstance)
		return;
	
	ABasePaperEnemy* Enemy = Cast<ABasePaperEnemy>(OwningInstance->GetOwningActor());
	
	if (!Enemy)
		return;
	
	Enemy->ExecuteAttackAction();
}

FName UPaperZDAnimNotify_Attack::GetDisplayName_Implementation() const
{
	return Super::GetDisplayName_Implementation();
}
