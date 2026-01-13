// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/QuestGiverDialogueNode.h"

#include "Subsystem/Player/QuestSubsystem.h"

void UQuestGiverDialogueNode::ExecuteNode(FGameDialogueContext DialogueContext)
{
	Super::ExecuteNode(DialogueContext);

	const auto PlayerController = DialogueContext.PlayerController;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UQuestGiverDialogueNode::ExecuteNode: PlayerController is null."));
		return;
	}
	auto* QuestSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UQuestSubsystem>();
	if (!QuestSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UQuestGiverDialogueNode::ExecuteNode: QuestSubsystem is null."));
		return;
	}

	QuestSubsystem->SetQuest(DialogueContext.PlayerController, QuestData);
}

FDialogueResult UQuestGiverDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	return FDialogueResult{
		EDialogueFlowType::Continue,
		EDialogueResultType::None,
		FGameplayTag::EmptyTag,
		false,
		false,
		FText::GetEmpty(),
		{}
	};
}
