// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Quests/System/QuestSystem.h"

#include "Systems/Quests/Quest/Quest.h"

void UQuestSystem::SetQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData)
{
	ExitCurrentQuest();
	EnterQuest(QuestInstigator, QuestData);
}

TScriptInterface<IQuestInterface> UQuestSystem::GetQuest() const
{
	if (CurrentQuest)
	{
		return CurrentQuest;
	}

	return nullptr;
}

void UQuestSystem::ClearQuest()
{
	ExitCurrentQuest();
	CurrentQuest = nullptr;
}

FOnQuestSystemCompleted& UQuestSystem::GetOnQuestSystemCompletedHandle()
{
	return OnQuestSystemCompleted;
}

FOnQuestSystemUpdated& UQuestSystem::GetOnQuestSystemUpdatedHandle()
{
	return OnQuestSystemUpdated;
}

FOnQuestSystemChanged& UQuestSystem::GetOnQuestSystemChangedHandle()
{
	return OnQuestSystemChanged;
}

// TODO: This can't be marked const because of the stupid dynamic delegate. Look into
void UQuestSystem::HandleQuestCompleted()
{
	OnQuestSystemCompleted.Broadcast();
}

void UQuestSystem::HandleQuestUpdated()
{
	OnQuestSystemUpdated.Broadcast();
}

void UQuestSystem::UnsubscribeFromCurrentQuest()
{
	if (!CurrentQuest)
	{
		checkf(false, TEXT("UQuestSystem::UnsubscribeFromCurrentQuest Tried to unsubscribe from a null quest"));
		return;
	}

	CurrentQuest->GetOnQuestCompletedHandle().RemoveDynamic(this, &UQuestSystem::HandleQuestCompleted);
}

void UQuestSystem::SubscribeToCurrentQuest()
{
	if (!CurrentQuest)
	{
		checkf(false, TEXT("UQuestSystem::SubscribeToCurrentQuest Tried to subscribe to a null quest"));
		return;
	}

	CurrentQuest->GetOnQuestCompletedHandle().AddDynamic(this, &UQuestSystem::HandleQuestCompleted);
	CurrentQuest->GetOnQuestUpdatedHandle().AddDynamic(this, &UQuestSystem::HandleQuestUpdated);
}

void UQuestSystem::EnterQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData)
{
	CurrentQuest = NewObject<UQuest>(this, UQuest::StaticClass());

	checkf(CurrentQuest, TEXT("UQuestSystem::EnterQuest was called with a null quest"));

	if (CurrentQuest)
	{
		SubscribeToCurrentQuest();
		CurrentQuest->InitQuest(QuestInstigator, QuestData);
	}

	OnQuestSystemChanged.Broadcast(CurrentQuest);
}

void UQuestSystem::ExitCurrentQuest()
{
	if (CurrentQuest)
	{
		CurrentQuest->ExitQuest();
		UnsubscribeFromCurrentQuest();
	}
}
