// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Quests/QuestInterface.h"
#include "Systems/Quests/Condition/BaseQuestCondition.h"
#include "UObject/Object.h"
#include "Quest.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UQuest : public UObject, public IQuestInterface
{
	GENERATED_BODY()

public:
	virtual void InitQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData) override;
	virtual void ExitQuest() override;

	virtual FString GetQuestName() const override;
	virtual FGameplayTag GetQuestStartedTag() const override;
	virtual FGameplayTag GetQuestFinishedTag() const override;

	virtual int GetNrOfCompletions() const override;
	virtual int GetNrOfConditions() const override;
	
	virtual FString GetConditionDescription(int ConditionIndex) const override;
	virtual FOnQuestCompleted& GetOnQuestCompletedHandle() override;
	virtual FOnQuestUpdated& GetOnQuestUpdatedHandle() override;

public:
	FOnQuestCompleted OnQuestCompleted;
	FOnQuestUpdated OnQuestUpdated;

private:
	FString QuestName;
	FGameplayTag QuestStartedTag;
	FGameplayTag QuestFinishedTag;
	int NrOfCompletions;
	UPROPERTY()
	TArray<TObjectPtr<UBaseQuestCondition>> Conditions;

private:
	int NrOfConditionsMet = 0;

private:
	void SubscribeToConditions();
	void UnsubscribeFromConditions();

private:
	UFUNCTION()
	void HandleConditionMet(TScriptInterface<IQuestConditionInterface> ConditionMet);
};
