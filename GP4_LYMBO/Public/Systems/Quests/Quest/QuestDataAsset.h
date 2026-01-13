// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Systems/Quests/Condition/BaseQuestCondition.h"
#include "GameplayTagContainer.h"
#include "QuestDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UQuestDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
	FGameplayTag QuestStartedTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
	FGameplayTag QuestFinishedTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
	FString QuestName;

	UPROPERTY(Instanced, EditDefaultsOnly, BlueprintReadOnly, Category="Quest")
	TArray<TObjectPtr<UBaseQuestCondition>> Conditions;
};
