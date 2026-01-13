// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/OptionNode.h"

#include "Systems/Dialogue/DialogueContext/GameDialogueContext.h"

FDialogueResult UOptionNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	// TODO: Some options may want to close dialogue after choice.
	FDialogueResult Result = FDialogueResult{
		EDialogueFlowType::End,
		EDialogueResultType::Option,
		FGameplayTag::EmptyTag,
		false,
		false,
		FText::GetEmpty(),
		{}
	};

	for (const auto& Option : Options)
	{
		Result.Options.Add({Option.Text});
	}

	return Result;
}

void UOptionNode::PickOption(const FGameDialogueContext& DialogueContext, int OptionIndex)
{
	if (!Options.IsValidIndex(OptionIndex))
	{
		checkf(false, TEXT("OptionIndex is out of bounds."));
		return;
	}

	if (Options[OptionIndex].OnChosen)
	{
		Options[OptionIndex].OnChosen->ExecuteNode(DialogueContext);
	}
	else
	{
		// checkf(false, TEXT("OnChosen node is null."));
		UE_LOG(LogTemp, Display, TEXT("OnChosen node is null."));
	}
}
