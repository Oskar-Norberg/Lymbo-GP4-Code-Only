// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/IntegerComparisonConditionalDialogueNode.h"

#include "Systems/Dialogue/Data/DialogueDataInterface.h"

bool UIntegerComparisonConditionalDialogueNode::CanExecute(const FGameDialogueContext& DialogueContext) const
{
	int FoundValue = 0;
	const auto KeyFound = DialogueContext.DialogueDataSystem->TryGetInt(ConditionKey, FoundValue);

	if (KeyFound && FoundValue == ExpectedValue)
	{
		return true;
	}

	return false;
}

FDialogueResult UIntegerComparisonConditionalDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
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
