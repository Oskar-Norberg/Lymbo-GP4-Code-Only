#include "Entities/Item.h"

void UItem::InitializeItem(FGameplayTag SomeItemTag)
{
	ItemTag = SomeItemTag;
}

FGameplayTag UItem::GetItemTag() const
{
	return ItemTag;
}
