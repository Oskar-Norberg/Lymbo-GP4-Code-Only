#include "Interactable/NPCInteractableComponent.h"


UNPCInteractableComponent::UNPCInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UNPCInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UNPCInteractableComponent::DoesInteractorHaveRequiredItems()
{
	UInventoryComponent* InteractorInventory = nullptr;
	bool InteractorHasRequiredItems = true;
	TMap<FGameplayTag, int> MissingItemsMap;
	
	if (CurrentInteractionContext != nullptr && CurrentInteractionContext->GetCurrentSourceController())
	{
		InteractorInventory = CurrentInteractionContext->GetCurrentSourceController()
		->GetPawn()->FindComponentByClass<UInventoryComponent>();
		
		if (InteractorInventory != nullptr)
		{
			for (auto& RequiredItem : RequirementsList)
			{
				if (InteractorInventory->HasItem(RequiredItem.Key))
				{
					if (InteractorInventory->GetInventoryInstance()
						->ItemsInInventory[RequiredItem.Key].Amount < RequiredItem.Value)
					{
						MissingItemsMap.Add(RequiredItem.Key,
							RequiredItem.Value -
							InteractorInventory->GetInventoryInstance()->ItemsInInventory[RequiredItem.Key].Amount);
						InteractorHasRequiredItems = false;
					}
				}
				else
				{
					MissingItemsMap.Add(RequiredItem.Key, RequiredItem.Value);
					InteractorHasRequiredItems = false;
				}
			}
		}
	}
	else
	{
		InteractorHasRequiredItems = false;
	}

	if (!InteractorHasRequiredItems)
	{
		ListMissingItems(MissingItemsMap);
	}
	return InteractorHasRequiredItems;
}

void UNPCInteractableComponent::ListMissingItems_Implementation(TMap<FGameplayTag, int>& MissingItemsMap)
{
	for (auto& Item : MissingItemsMap)
	{
		GEngine->AddOnScreenDebugMessage(-1,
			5, FColor::Orange,
			FString::Printf(TEXT("%s : %d"), *Item.Key.GetTagLeafName().ToString(), Item.Value));
	}
}

void UNPCInteractableComponent::GiveInteractorItem(FGameplayTag ItemTag, int Amount)
{
	if (CurrentInteractionContext != nullptr && CurrentInteractionContext->GetCurrentSourceController())
	{
		UInventoryComponent* InteractorInventoryComponent = CurrentInteractionContext
		->GetCurrentSourceController()->GetPawn()->FindComponentByClass<UInventoryComponent>();

		if (InteractorInventoryComponent != nullptr)
		{
			InteractorInventoryComponent->AddItemToInventory(ItemTag, Amount);
		}
	}
}

void UNPCInteractableComponent::TakeItemFromInteractor(FGameplayTag ItemTag)
{
	if (CurrentInteractionContext != nullptr && CurrentInteractionContext->GetCurrentSourceController() &&
		RequirementsList.Contains(ItemTag))
	{
		UInventoryComponent* InteractorInventoryComponent = CurrentInteractionContext
		->GetCurrentSourceController()->GetPawn()->FindComponentByClass<UInventoryComponent>();

		if (InteractorInventoryComponent != nullptr)
		{
			InteractorInventoryComponent->RemoveItemFromInventory(ItemTag, RequirementsList[ItemTag]);
		}
	}
}

void UNPCInteractableComponent::BroadcastOnDialogueInitiated()
{
	OnDialogueInitiated.Broadcast();
}

void UNPCInteractableComponent::BroadcastOnDialogueProgressed(FDialogueResult DialogueResult)
{
	OnDialogueProgressed.Broadcast(DialogueResult);
}

void UNPCInteractableComponent::BroadcastOnDialogueExited()
{
	OnDialogueExited.Broadcast();
}


