// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/Nodes/Formattable/Input/MissingItemDataGetter.h"
#include "Components/Player Components/Inventory/InventoryComponent.h"

FText UMissingItemDataGetter::GetText(const FGameDialogueContext& DialogueContext) const
{
	const auto PlayerController = DialogueContext.PlayerController;
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryConditionalDialogueNode::CanExecute: PlayerController is null."));
		return FText::GetEmpty();
	}
	const auto Pawn = PlayerController->GetPawn();
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryConditionalDialogueNode::CanExecute: Pawn is null."));
		return FText::GetEmpty();
	}
	const auto InventoryComponent = Pawn->FindComponentByClass<UInventoryComponent>();
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryConditionalDialogueNode::CanExecute: InventoryComponent is null."));
		return FText::GetEmpty();
	}

	FText Output;
	for (const auto& ItemTag : ItemTags)
	{
		if (!ItemTag.IsValid())
		{
			continue;
		}

		// TODO: This leaves a trailing comma. fuck you
		if (!InventoryComponent->HasItem(ItemTag))
		{
			Output = FText::Format(
				FText::FromString(TEXT("{0}{1}, ")),
				Output,
				FText::FromName(ItemTag.GetTagLeafName())
			);
		}
	}

	return Output;
}
