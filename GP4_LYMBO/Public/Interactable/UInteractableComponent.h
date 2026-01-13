#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Systems/Interactions/InteractionBase.h"
#include "UInteractableComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class GP4_LYMBO_API UInteractableComponent : public UActorComponent, public IInteractable_Interface
{
	GENERATED_BODY()

public:
	UInteractableComponent();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FGameplayTag InteractionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable")
	TMap<FGameplayTag, int> RequirementsList;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	UInteractionBase* CurrentInteractionContext = nullptr;


protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Interactable")
	bool InteractableNeedsRequirementsToBeInteractedWith = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable")
	bool InteractableIsTicked = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable")
	bool InteractableTicksOutsideOfInteraction = false;

	UPROPERTY(BlueprintReadWrite, Category = "Interactable")
	bool IsBeingInteractedWith = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
	bool LocksPlayer = false;

public:
	virtual FGameplayTag GetInteractionTag_Implementation() override;
	virtual bool CanInteract(const AController* SomeSourceController) override;
	virtual void BeginInteraction_Implementation() override;
	virtual void EndInteraction_Implementation() override;
	virtual void SetInteractionContext_Implementation(UInteractionBase* InteractionContext) override;
	virtual AActor* GetActorAssociatedWithInteractable_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual void StopBeingInteractedWith();

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	bool DoesInteractorMeetRequirements(const AController* SomeSourceController);
};
