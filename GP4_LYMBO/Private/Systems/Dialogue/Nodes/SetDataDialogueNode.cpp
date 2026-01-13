// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Dialogue/Nodes/SetDataDialogueNode.h"

#include "Systems/Dialogue/Data/DialogueDataInterface.h"

FDialogueResult USetDataDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	const FDialogueResult DialogueResult
	{
		EDialogueFlowType::Continue,
		EDialogueResultType::None,
		FGameplayTag::EmptyTag,
		false,
		false,
		FText::GetEmpty(),
		{}
	};

	return DialogueResult;
}

void USetDataDialogueNode::ExecuteNode(FGameDialogueContext DialogueContext)
{
	Super::ExecuteNode(DialogueContext);

	if (BoolValue.IsSet())
	{
		DialogueContext.DialogueDataSystem->SetBool(Key, BoolValue.GetValue());
	}
	if (StringValue.IsSet())
	{
		DialogueContext.DialogueDataSystem->SetString(Key, StringValue.GetValue());
	}
	if (IntValue.IsSet())
	{
		DialogueContext.DialogueDataSystem->SetInt(Key, IntValue.GetValue());
	}
}
