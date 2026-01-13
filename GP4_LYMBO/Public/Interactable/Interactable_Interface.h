#pragma once

#include "CoreMinimal.h"
#include "Components/Player Components/Inventory/InventoryComponent.h"
#include "UObject/Object.h"
#include "Interactable_Interface.generated.h"


class UInteractionBase;
class NonconditionalInteractableComponent;

UINTERFACE()
class UInteractable_Interface : public UInterface
{
	GENERATED_BODY()
};

class IInteractable_Interface
{
	GENERATED_BODY()
	
public:
	virtual bool CanInteract(const AController* SomeSourceController) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	FGameplayTag GetInteractionTag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void BeginInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void EndInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void SetInteractionContext(UInteractionBase* InteractionContext);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	AActor* GetActorAssociatedWithInteractable();
};