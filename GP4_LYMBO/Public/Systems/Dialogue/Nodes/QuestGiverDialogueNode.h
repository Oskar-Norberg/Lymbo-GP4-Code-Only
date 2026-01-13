// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "Systems/Quests/Quest/QuestDataAsset.h"
#include "QuestGiverDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UQuestGiverDialogueNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dialogue/Quest")
	TObjectPtr<UQuestDataAsset> QuestData;

public:
	virtual void ExecuteNode(FGameDialogueContext DialogueContext) override;
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
