#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Entities/Item.h"
#include "UniversalItemData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API UUniversalItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	TMap<FGameplayTag, FItemData> ItemDataMap;
};
