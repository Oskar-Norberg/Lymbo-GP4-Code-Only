#include "Components/Player Components/Interaction/InteractionComponent.h"

#include "Interactable/Interactable_Interface.h"
#include "Interactable/UInteractableComponent.h"
#include "Subsystem/Instance/Interaction Subsystem/UniversalInteractionSubsystem.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DoInteractionTrace();
}

void UInteractionComponent::TryInteractingWithObject(AActor* ActorFound)
{
	if (ActorFound != nullptr && CurrentInteractionContext == nullptr)
	{
		UActorComponent* ActorInteractable =
			ActorFound->FindComponentByInterface(UInteractable_Interface::StaticClass());

		if (ActorInteractable != nullptr)
		{
			FGameplayTag TagForInteractionContext =
			IInteractable_Interface::Execute_GetInteractionTag(ActorInteractable);

			if (TagForInteractionContext.IsValid())
			{
				UInteractionBase* InteractionContext = GetWorld()->GetGameInstance()->
													   GetSubsystem<UUniversalInteractionSubsystem>()->GetInteraction(
														   TagForInteractionContext);

				if (InteractionContext != nullptr)
				{
					if (IInteraction_Interface::Execute_TryInteraction(
						InteractionContext,
						Cast<APawn>(GetOwner())->GetController(),
						this,
						ActorInteractable))
					{
						CurrentInteractionContext = InteractionContext;
						CurrentInteractable = ActorInteractable;
						IInteraction_Interface::Execute_BeginInteraction(CurrentInteractionContext);
					}
				}
			}
		}
	}
}

void UInteractionComponent::BeginInteraction_Implementation()
{
}

void UInteractionComponent::EndInteraction_Implementation()
{
	CurrentInteractable = nullptr;
	CurrentInteractionContext = nullptr;
}

void UInteractionComponent::StopInteractingWithObject()
{
	if (CurrentInteractable != nullptr && CurrentInteractionContext != nullptr)
	{
		IInteraction_Interface::Execute_EndInteraction(CurrentInteractionContext);
	}
}

bool UInteractionComponent::IsInteractableInFrontOfOwner(AActor* Interactable)
{
	if (Interactable != nullptr)
	{
		FVector DirectionalVectorFromOwner = Interactable->GetActorTransform().GetLocation()
			- GetOwner()->GetActorTransform().GetLocation();

		DirectionalVectorFromOwner.Normalize();

		FVector OwnerForwardVector = GetOwner()->GetActorForwardVector();
		OwnerForwardVector.Normalize();

		float DotProduct = FVector::DotProduct(DirectionalVectorFromOwner,
		                                       OwnerForwardVector);

		if (DotProduct > DotProductInteractionLimit)
		{
			return true;
		}
	}
	return false;
}
