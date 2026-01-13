#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/Image.h"
#include "UObject/Object.h"
#include "Item.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemDisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* ItemImage;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API UItem : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag ItemTag;

public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	void InitializeItem(FGameplayTag SomeItemTag);

	UFUNCTION(BlueprintCallable, Category = "Item")
	FGameplayTag GetItemTag() const;
};


