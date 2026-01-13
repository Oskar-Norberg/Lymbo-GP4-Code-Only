// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/StatementNode.h"

FDialogueResult UStatementNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	return FDialogueResult{
		EDialogueFlowType::End,
		EDialogueResultType::Statement,
		SpeakerTag,
		DoCloseDialogue,
		false,
		Text,
		{},
		FString(),
		Animations
	};
}
