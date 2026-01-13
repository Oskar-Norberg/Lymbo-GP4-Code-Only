// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/PublishEventBusNode.h"

#include "Subsystem/World/WorldEventBus.h"

void UPublishEventBusNode::ExecuteNode(FGameDialogueContext DialogueContext)
{
	Super::ExecuteNode(DialogueContext);

	const auto PlayerController = DialogueContext.PlayerController;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPublishEventBusNode::ExecuteNode: PlayerController is null."));
		return;
	}
	auto* WorldEventBus = PlayerController->GetWorld()->GetSubsystem<UWorldEventBus>();
	if (!WorldEventBus)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPublishEventBusNode::ExecuteNode: WorldEventBus is null."));
		return;
	}

	WorldEventBus->Publish(EventData, EventData->GetClass());
}

FDialogueResult UPublishEventBusNode::GetResult(const FGameDialogueContext& DialogueContext)
{
	if (DoForceClose)
	{
		return FDialogueResult{
			EDialogueFlowType::End,
			EDialogueResultType::None,
			FGameplayTag::EmptyTag,
			DoForceClose,
			DoForceClose,
			FText::GetEmpty(),
			{}
		};
	}
	return FDialogueResult{
		EDialogueFlowType::Continue,
		EDialogueResultType::None,
		FGameplayTag::EmptyTag,
		DoForceClose,
		DoForceClose,
		FText::GetEmpty(),
		{}
	};
}
