#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Amount = 0;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API UInventoryInstance : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<FGameplayTag, FInventorySlot> ItemsInInventory;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class GP4_LYMBO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FGameplayTag InventoryItemTag, int Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromInventory(FGameplayTag InventoryItemTag, int Amount);

	UFUNCTION(BlueprintCallable)
	bool HasItem(FGameplayTag ItemToBeFound);

	UFUNCTION(BlueprintCallable)
	UInventoryInstance* GetInventoryInstance();

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TMap<FGameplayTag, int> InventoryPreset;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	UInventoryInstance* InventoryInstance = nullptr;
};
