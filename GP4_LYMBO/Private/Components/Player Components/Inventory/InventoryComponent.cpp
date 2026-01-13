#include "Components/Player Components/Inventory/InventoryComponent.h"
#include "GameplayTags.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryInstance = NewObject<UInventoryInstance>(this);
	
	if (InventoryPreset.Num() > 0)
	{
		for (auto& ItemInPreset : InventoryPreset)
		{
			AddItemToInventory(ItemInPreset.Key, ItemInPreset.Value);
		}
	}

	InventoryPreset.Empty();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItemToInventory(FGameplayTag InventoryItemTag, int Amount = 1)
{
	if (InventoryInstance->ItemsInInventory.Contains(InventoryItemTag))
	{
		InventoryInstance->ItemsInInventory[InventoryItemTag].Amount += Amount;
	}
	else
	{
		InventoryInstance->ItemsInInventory.Add(InventoryItemTag,
			FInventorySlot(InventoryItemTag.GetTagLeafName(), Amount));
	}
}

void UInventoryComponent::RemoveItemFromInventory(FGameplayTag InventoryItemTag, int Amount = 1)
{
	if (InventoryInstance->ItemsInInventory.Contains(InventoryItemTag))
	{
		FInventorySlot& InventorySlot = InventoryInstance->ItemsInInventory[InventoryItemTag];
		InventorySlot.Amount -= Amount;
		if (InventorySlot.Amount <= 0)
		{
			InventoryInstance->ItemsInInventory.Remove(InventoryItemTag);
		}
	}
}

bool UInventoryComponent::HasItem(FGameplayTag ItemToBeFound)
{
	return InventoryInstance->ItemsInInventory.Contains(ItemToBeFound);
}

UInventoryInstance* UInventoryComponent::GetInventoryInstance()
{
	return InventoryInstance;
}

