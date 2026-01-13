// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Quests/Quest/Quest.h"

// This function would benefit from some cleaning
void UQuest::InitQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData)
{
	IQuestInterface::InitQuest(QuestInstigator, QuestData);

	checkf(QuestData, TEXT("UQuest::InitQuest: QuestData is null"));

	QuestStartedTag = QuestData->QuestStartedTag;
	QuestFinishedTag = QuestData->QuestFinishedTag;
	QuestName = QuestData->QuestName;
	NrOfCompletions = 0;

	Conditions.Empty();
	for (const auto& Condition : QuestData->Conditions)
	{
		if (!Condition)
		{
			UE_LOG(LogTemp, Warning, TEXT("UQuest::InitQuest: QuestData contains null condition"));
			continue;
		}

		// Make a copy to avoid modifying the original DataAsset
		const auto& CopiedCondition = DuplicateObject(Condition, this);

		UBaseQuestCondition::Execute_InitCondition(CopiedCondition, QuestInstigator);
		Conditions.Add(CopiedCondition);
	}

	SubscribeToConditions();
}

void UQuest::ExitQuest()
{
	IQuestInterface::ExitQuest();

	for (const auto& Condition : Conditions)
	{
		if (Condition && IsValid(Condition.Get()))
		{
			UBaseQuestCondition::Execute_ExitCondition(Condition);
		}
	}

	UnsubscribeFromConditions();
}

FString UQuest::GetQuestName() const
{
	return QuestName;
}

FGameplayTag UQuest::GetQuestStartedTag() const
{
	return QuestStartedTag;
}

FGameplayTag UQuest::GetQuestFinishedTag() const
{
	return QuestFinishedTag;
}

int UQuest::GetNrOfCompletions() const
{
	return NrOfCompletions;
}

int UQuest::GetNrOfConditions() const
{
	return Conditions.Num();
}

FString UQuest::GetConditionDescription(int ConditionIndex) const
{
	if (Conditions.IsValidIndex(ConditionIndex))
	{
		return Conditions[ConditionIndex]->GetConditionName();
	}

	UE_LOG(LogTemp, Warning, TEXT("UQuest::GetConditionDescription called on invalid index"));
	return FString("Invalid Condition Index");
}

FOnQuestCompleted& UQuest::GetOnQuestCompletedHandle()
{
	return OnQuestCompleted;
}

FOnQuestUpdated& UQuest::GetOnQuestUpdatedHandle()
{
	return OnQuestUpdated;
}

void UQuest::SubscribeToConditions()
{
	for (const auto& Condition : Conditions)
	{
		Condition->OnConditionMet.AddDynamic(this, &UQuest::HandleConditionMet);
	}
}

void UQuest::UnsubscribeFromConditions()
{
	for (const auto& Condition : Conditions)
	{
		if (Condition && IsValid(Condition.Get()))
		{
			Condition->OnConditionMet.RemoveDynamic(this, &UQuest::HandleConditionMet);
		}
	}
}

void UQuest::HandleConditionMet(TScriptInterface<IQuestConditionInterface> ConditionMet)
{
	NrOfCompletions++;

	OnQuestUpdated.Broadcast();
	if (NrOfCompletions >= Conditions.Num())
	{
		OnQuestCompleted.Broadcast();
	}
}
