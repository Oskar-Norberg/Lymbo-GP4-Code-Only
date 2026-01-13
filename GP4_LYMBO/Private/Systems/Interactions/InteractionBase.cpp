#include "Systems/Interactions/InteractionBase.h"
#include "Components/Player Components/Interaction/InteractionComponent.h"
#include "Interactable/Interactable_Interface.h"
#include "Kismet/GameplayStatics.h"

void UInteractionBase::BeginPlay()
{
	InteractionSubsystem = Cast<ULymboGameInstance>(GetWorld()->GetGameInstance());
	checkf(InteractionSubsystem != nullptr, TEXT("INVALID OUTER FOR INTERACTION BASE"));
}

bool UInteractionBase::TryInteraction_Implementation(AController* SomeSourceController,
                                                     const TScriptInterface<IInteractor_Interface>& SomeSourceInteractor,
                                                     const TScriptInterface<IInteractable_Interface>& SomeTargetInteractable)
{
	bool InteractionPossible = false;

	//checks if interactor can interact with the interactable
	InteractionPossible = SomeTargetInteractable->CanInteract(SomeSourceController); 
		
	if (InteractionPossible)
	{
		CurrentInteractableTarget = SomeTargetInteractable;
		CurrentSourceController = SomeSourceController;
		CurrentSourceInteractor = SomeSourceInteractor;
		IInteractable_Interface::Execute_SetInteractionContext(CurrentInteractableTarget.GetObject(), this);
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green,
			TEXT("Interaction Possible"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red,
TEXT("Interaction Not Possible"));
	}
	
	return InteractionPossible;
}

void UInteractionBase::BeginInteraction_Implementation()
{
	IInteractor_Interface::Execute_BeginInteraction(CurrentSourceInteractor.GetObject());
	IInteractable_Interface::Execute_BeginInteraction(CurrentInteractableTarget.GetObject());
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Blue,
    TEXT("Interaction Begun"));
}

void UInteractionBase::EndInteraction_Implementation()
{
	IInteractor_Interface::Execute_EndInteraction(CurrentSourceInteractor.GetObject());
	IInteractable_Interface::Execute_EndInteraction(CurrentInteractableTarget.GetObject());
	
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Blue,
        TEXT("Interaction Ended"));

	CurrentSourceInteractor = nullptr;
	CurrentInteractableTarget = nullptr;
	CurrentSourceController = nullptr;
}

UWorld* UInteractionBase::GetWorld() const
{
	return GetOuter()->GetWorld();
}

UGameInstance* UInteractionBase::GetGameInstance() const
{
	return GetWorld()->GetGameInstance();
}

AActor* UInteractionBase::GetActorOfClass(UClass* SomeActorClass)
{
	return UGameplayStatics::GetActorOfClass(GetWorld(), SomeActorClass);
}

AController* UInteractionBase::GetCurrentSourceController()
{
	return CurrentSourceController;
}

TScriptInterface<IInteractor_Interface> UInteractionBase::GetCurrentInteractor()
{
	return CurrentSourceInteractor;
}

TScriptInterface<IInteractable_Interface> UInteractionBase::GetCurrentInteractable()
{
	return CurrentInteractableTarget;
}
