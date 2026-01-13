#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UniversalInteractionSubsystemData.generated.h"

class UInteractionBase;

USTRUCT(BlueprintType, Blueprintable)
struct FInteractionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InteractionTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UInteractionBase> InteractionLogicSubclass;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API UUniversalInteractionSubsystemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInteractionData> InteractionDataArray;
};
