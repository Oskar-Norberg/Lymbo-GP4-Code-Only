// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Systems/Quests/QuestSystemInterface.h"
#include "Systems/Quests/System/QuestSystem.h"
#include "QuestSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UQuestSubsystem : public ULocalPlayerSubsystem, public IQuestSystemInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void SetQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData) override;


	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IQuestInterface> GetQuest() const override;

public:
	UPROPERTY(BlueprintAssignable, Category="Quest System")
	FOnQuestSystemCompleted OnQuestSystemCompleted;
	UPROPERTY(BlueprintAssignable, Category="Quest System")
	FOnQuestSystemUpdated OnQuestSystemUpdated;
	UPROPERTY(BlueprintAssignable, Category="Quest System")
	FOnQuestSystemChanged OnQuestSystemChanged;

public:
	// Wraps the QuestSystem's delegates for blueprint access.
	virtual FOnQuestSystemCompleted& GetOnQuestSystemCompletedHandle() override;
	virtual FOnQuestSystemUpdated& GetOnQuestSystemUpdatedHandle() override;
	virtual FOnQuestSystemChanged& GetOnQuestSystemChangedHandle() override;

private:
	UPROPERTY()
	TObjectPtr<UQuestSystem> QuestSystem;

private:
	UFUNCTION()
	void HandleOnQuestSystemCompleted();
	UFUNCTION()
	void HandleOnQuestSystemUpdated();
	UFUNCTION()
	void HandleOnQuestSystemChanged(TScriptInterface<IQuestInterface> NewQuest);
};
