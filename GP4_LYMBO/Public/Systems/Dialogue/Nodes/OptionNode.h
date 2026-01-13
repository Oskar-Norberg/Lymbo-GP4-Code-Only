// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "OptionNode.generated.h"

USTRUCT(BlueprintType)
struct FDialogueOption
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/Options")
	FText Text = FText::GetEmpty();

	// TODO: Since picking an option will only lead to its "execute" behaviour, storing any BaseNode here is confusing.
	// A designer will try to add a StatementNode here and nothing will happen. And you will be sad.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Dialogue/Options")
	TObjectPtr<UDialogueNodeBase> OnChosen = nullptr;
};

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UOptionNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TArray<FDialogueOption> Options;

public:
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
	virtual void PickOption(const FGameDialogueContext& DialogueContext, int OptionIndex) override;
};
