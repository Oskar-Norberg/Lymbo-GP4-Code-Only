// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Quests/Implementation/Condition/UWaitCondition.h"

void UWaitCondition::InitCondition_Implementation(const AController* QuestInstigator)
{
	Super::InitCondition_Implementation(QuestInstigator);

	GetWorld()->GetTimerManager().SetTimer(WaitTimer, this, &UWaitCondition::HandleWaitTimerFinished,
										   WaitTime / 1000.0f,
										   false);
}

void UWaitCondition::HandleWaitTimerFinished()
{
	OnConditionMet.Broadcast(this);
}
