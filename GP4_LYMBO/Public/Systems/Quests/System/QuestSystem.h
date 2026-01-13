// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Quests/QuestInterface.h"
#include "Systems/Quests/QuestSystemInterface.h"
#include "Systems/Quests/Quest/Quest.h"
#include "UObject/Object.h"
#include "QuestSystem.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UQuestSystem : public UObject, public IQuestSystemInterface
{
	GENERATED_BODY()

public:
	virtual void SetQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData) override;
	virtual TScriptInterface<IQuestInterface> GetQuest() const override;

	void ClearQuest();

	UPROPERTY()
	TObjectPtr<UQuest> CurrentQuest;

public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestSystemCompleted OnQuestSystemCompleted;
	UPROPERTY(BlueprintAssignable)
	FOnQuestSystemUpdated OnQuestSystemUpdated;
	UPROPERTY(BlueprintAssignable)
	FOnQuestSystemChanged OnQuestSystemChanged;

public:
	// For C++ access through the Interface.
	virtual FOnQuestSystemCompleted& GetOnQuestSystemCompletedHandle() override;
	virtual FOnQuestSystemUpdated& GetOnQuestSystemUpdatedHandle() override;
	virtual FOnQuestSystemChanged& GetOnQuestSystemChangedHandle() override;

private:
	UFUNCTION()
	void HandleQuestCompleted();

	UFUNCTION()
	void HandleQuestUpdated();

private:
	void UnsubscribeFromCurrentQuest();
	void SubscribeToCurrentQuest();

private:
	void EnterQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData);
	void ExitCurrentQuest();
};
