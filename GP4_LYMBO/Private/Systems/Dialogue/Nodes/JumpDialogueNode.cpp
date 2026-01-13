// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/JumpDialogueNode.h"

FDialogueResult UJumpDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	FDialogueResult DialogueResult{
		EDialogueFlowType::Jump,
		EDialogueResultType::None,
		FGameplayTag::EmptyTag,

		false,
		false,
		FText::GetEmpty(),
		{},
		TargetLabel
	};
	
	return DialogueResult;
}
