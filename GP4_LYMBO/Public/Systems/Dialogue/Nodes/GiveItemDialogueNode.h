// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "GiveItemDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UGiveItemDialogueNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue/Item")
	FGameplayTag ItemTag; 

public:
	virtual void ExecuteNode(FGameDialogueContext DialogueContext) override;
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
