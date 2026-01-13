// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "SetDataDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API USetDataDialogueNode : public UDialogueNodeBase
{
	GENERATED_BODY()
	
public:
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
	virtual void ExecuteNode(FGameDialogueContext DialogueContext) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/SetData")
	FString Key;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/SetData")
	TOptional<bool> BoolValue = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/SetData")
	TOptional<FString> StringValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/SetData")
	TOptional<int> IntValue;
};
