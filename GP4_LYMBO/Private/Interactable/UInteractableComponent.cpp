#include "Interactable/UInteractableComponent.h"


UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = InteractableIsTicked;
}

FGameplayTag UInteractableComponent::GetInteractionTag_Implementation()
{
	return InteractionTag;
}

bool UInteractableComponent::CanInteract(const AController* SomeSourceController)
{
	if (InteractableNeedsRequirementsToBeInteractedWith)
	{
		return DoesInteractorMeetRequirements(SomeSourceController);
	}
	return true;
}

bool UInteractableComponent::DoesInteractorMeetRequirements(const AController* SomeSourceController)
{
	bool bCanInteract = true;

	UInventoryInstance* InteractorInventory = nullptr;
	UInventoryComponent* SourceControllerInventoryComponent =
		SomeSourceController->GetPawn()->GetComponentByClass<UInventoryComponent>();

	if (SourceControllerInventoryComponent == nullptr)
	{
		bCanInteract = false;
		return false;
	}

	InteractorInventory = SourceControllerInventoryComponent->GetInventoryInstance();

	for (auto& ItemRequired : RequirementsList)
	{
		if (!InteractorInventory->ItemsInInventory.Contains(ItemRequired.Key))
		{
			bCanInteract = false;
			break;
		}
	}

	return bCanInteract;
}

void UInteractableComponent::BeginInteraction_Implementation()
{
	if (PrimaryComponentTick.bCanEverTick)
	{
		SetComponentTickEnabled(true);
	}
	IsBeingInteractedWith = true;
}

void UInteractableComponent::EndInteraction_Implementation()
{
	CurrentInteractionContext = nullptr;
	if (!PrimaryComponentTick.bCanEverTick)
	{
		SetComponentTickEnabled(false);
	}
	IsBeingInteractedWith = false;
}

void UInteractableComponent::SetInteractionContext_Implementation(UInteractionBase* InteractionContext)
{
	CurrentInteractionContext = InteractionContext;
}

AActor* UInteractableComponent::GetActorAssociatedWithInteractable_Implementation()
{
	return GetOwner();
}

void UInteractableComponent::StopBeingInteractedWith()
{
	IInteraction_Interface::Execute_EndInteraction(CurrentInteractionContext);
}


