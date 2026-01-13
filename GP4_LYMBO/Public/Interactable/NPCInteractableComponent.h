#pragma once

#include "CoreMinimal.h"
#include "UInteractableComponent.h"
#include "Components/ActorComponent.h"
#include "Systems/Dialogue/DialogueResult/FDialogueResult.h"
#include "NPCInteractableComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNPCOnDialogueInitiated);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNPCOnDialgoueProgressed, FDialogueResult, DialogueResult);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNPCOnDialogueExited);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_LYMBO_API UNPCInteractableComponent : public UInteractableComponent
{
	GENERATED_BODY()

public:
	UNPCInteractableComponent();

public:
	UPROPERTY(BlueprintAssignable, Category="NPC Interaction/Events")
	FNPCOnDialogueInitiated OnDialogueInitiated;

	UPROPERTY(BlueprintAssignable, Category="NPC Interaction/Events")
	FNPCOnDialgoueProgressed OnDialogueProgressed;

	UPROPERTY(BlueprintAssignable, Category="NPC Interaction/Events")
	FNPCOnDialogueExited OnDialogueExited;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool DoesInteractorHaveRequiredItems();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ListMissingItems(TMap<FGameplayTag, int>& MissingItemsMap);
	void ListMissingItems_Implementation(TMap<FGameplayTag, int>& MissingItemsMap);

	UFUNCTION(BlueprintCallable)
	void GiveInteractorItem(FGameplayTag ItemTag, int Amount);

	UFUNCTION(BlueprintCallable)
	void TakeItemFromInteractor(FGameplayTag ItemTag);

protected:
	UFUNCTION(BlueprintCallable)
	void BroadcastOnDialogueInitiated();
	UFUNCTION(BlueprintCallable)
	void BroadcastOnDialogueProgressed(FDialogueResult DialogueResult);
	UFUNCTION(BlueprintCallable)
	void BroadcastOnDialogueExited();
};




