// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "ConditionalDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UConditionalDialogueNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/Condition")
	FString ConditionKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/Condition")
	bool ExpectedValue = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Dialogue/Condition")
	TObjectPtr<UDialogueNodeBase> OnTrue = nullptr;

public:
	virtual bool CanExecute(const FGameDialogueContext& DialogueContext) const override;
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
