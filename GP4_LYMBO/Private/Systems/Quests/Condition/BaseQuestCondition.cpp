// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Quests/Condition/BaseQuestCondition.h"

FString UBaseQuestCondition::GetConditionName() const
{
	return ConditionName;
}

FOnQuestConditionMet& UBaseQuestCondition::GetOnConditionMetHandle()
{
	return OnConditionMet;
}

UWorld* UBaseQuestCondition::GetWorld() const
{
	return GetOuter()->GetWorld();
}

UWorldEventBus* UBaseQuestCondition::GetQuestWorldEventBus(const AController* Controller) const
{
	// Terrible function
	return Controller->GetWorld()->GetSubsystem<UWorldEventBus>();
}

void UBaseQuestCondition::BroadcastConditionMet()
{
	OnConditionMet.Broadcast(this);
}

UWorld* UBaseQuestCondition::GetConditionWorld() const
{
	return GetWorld();
}

UObject* UBaseQuestCondition::GetConditionOwner() const
{
	return GetOuter();
}
