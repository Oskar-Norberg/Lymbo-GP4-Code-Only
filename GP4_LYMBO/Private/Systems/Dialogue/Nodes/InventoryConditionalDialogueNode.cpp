// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/InventoryConditionalDialogueNode.h"

#include "Components/Player Components/Inventory/InventoryComponent.h"

bool UInventoryConditionalDialogueNode::CanExecute(const FGameDialogueContext& DialogueContext) const
{
	const auto PlayerController = DialogueContext.PlayerController;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryConditionalDialogueNode::CanExecute: PlayerController is null."));
		return false;
	}
	const auto Pawn = PlayerController->GetPawn();
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryConditionalDialogueNode::CanExecute: Pawn is null."));
		return false;
	}
	const auto InventoryComponent = Pawn->FindComponentByClass<UInventoryComponent>();
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryConditionalDialogueNode::CanExecute: InventoryComponent is null."));
		return false;
	}

	bool HasItems = true;

	for (const auto& ItemTag : ItemTags)
	{
		if (!ItemTag.IsValid())
		{
			continue;
		}
		
		if (!InventoryComponent->HasItem(ItemTag))
		{
			HasItems = false;
			break;
		}
	}

	return HasItems;
}

FDialogueResult UInventoryConditionalDialogueNode::GetResult(const FGameDialogueContext& DialogueContext)
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
