// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/ProgressionConditionalDialogueNode.h"

#include "Subsystem/Instance/ProgressionSubsystem/ProgressionSubsystem.h"

bool UProgressionConditionalDialogueNode::CanExecute(const FGameDialogueContext& DialogueContext) const
{
	const auto PlayerController = DialogueContext.PlayerController;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UProgressionConditionalDialogueNode::CanExecute Could not access PlayerController"));
		return false;
	}
	const auto* ProgressionSubsystem = PlayerController->GetWorld()->GetGameInstance()->GetSubsystem<UProgressionSubsystem>();
	if (!ProgressionSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UProgressionConditionalDialogueNode::CanExecute Could not access ProgressionSubsystem"));
		return false;
	}
	bool HasTag = ProgressionSubsystem->HasAllTags(Conditions);

	if (HasTag == ExpectedHas)
	{
		return true;
	}

	return false;
}

FDialogueResult UProgressionConditionalDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
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
