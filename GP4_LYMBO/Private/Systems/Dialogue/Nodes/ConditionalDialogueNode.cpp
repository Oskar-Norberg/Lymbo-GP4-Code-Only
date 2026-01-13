// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/ConditionalDialogueNode.h"

#include "Systems/Dialogue/Data/DialogueDataInterface.h"

bool UConditionalDialogueNode::CanExecute(const FGameDialogueContext& DialogueContext) const
{
	bool FoundValue = false;
	// NOTE: Currently ignores the case where the key is not found. This should be fine?
	const auto KeyFound = DialogueContext.DialogueDataSystem->TryGetBool(ConditionKey, FoundValue);

	if (FoundValue == ExpectedValue)
	{
		return true;
	}

	return false;
}

FDialogueResult UConditionalDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	FDialogueResult Result;
	if (OnTrue)
	{
		OnTrue->ExecuteNode(DialogueContext);
		Result = OnTrue->GetResult(DialogueContext);
	}
	else
	{
		Result = FDialogueResult{
			EDialogueFlowType::Continue,
			EDialogueResultType::None,
			FGameplayTag::EmptyTag,
			false,
			false,
			FText::GetEmpty(),
			{}
		};
	}

	return Result;
}
