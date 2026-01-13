// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/GiveItemDialogueNode.h"

#include "Components/Player Components/Inventory/InventoryComponent.h"

void UGiveItemDialogueNode::ExecuteNode(FGameDialogueContext DialogueContext)
{
	Super::ExecuteNode(DialogueContext);

	const auto PlayerController = DialogueContext.PlayerController;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPublishEventBusNode::ExecuteNode: PlayerController is null."));
		return;
	}
	const auto PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPublishEventBusNode::ExecuteNode: PlayerPawn is null."));
		return;
	}
	const auto InventoryComponent = PlayerPawn->FindComponentByClass<UInventoryComponent>();
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPublishEventBusNode::ExecuteNode: InventoryComponent is null."));
		return;
	}
	
	InventoryComponent->AddItemToInventory(ItemTag, 1);
}

FDialogueResult UGiveItemDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
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