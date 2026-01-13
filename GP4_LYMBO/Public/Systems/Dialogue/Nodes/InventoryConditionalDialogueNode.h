// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "InventoryConditionalDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UInventoryConditionalDialogueNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer ItemTags;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Dialogue/Condition")
	TObjectPtr<UDialogueNodeBase> OnTrue = nullptr;

public:
	virtual bool CanExecute(const FGameDialogueContext& DialogueContext) const override;
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
