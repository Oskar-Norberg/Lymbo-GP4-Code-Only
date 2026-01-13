#pragma once

#include "CoreMinimal.h"
#include "Interactor_Interface.h"
#include "Interactable/Interactable_Interface.h"
#include "UObject/Object.h"
#include "Interaction_Interface.generated.h"


UINTERFACE()
class UInteraction_Interface : public UInterface
{
	GENERATED_BODY()
};

class IInteraction_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	bool TryInteraction(AController* SomeSourceController,
		const TScriptInterface<IInteractor_Interface>& SomeSourceInteractor,
		const TScriptInterface<IInteractable_Interface>& SomeTargetInteractable);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void BeginInteraction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void EndInteraction();
};
