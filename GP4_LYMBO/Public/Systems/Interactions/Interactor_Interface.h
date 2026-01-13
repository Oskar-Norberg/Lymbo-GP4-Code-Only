#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interactor_Interface.generated.h"


UINTERFACE()
class UInteractor_Interface : public UInterface
{
	GENERATED_BODY()
};

class IInteractor_Interface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BeginInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndInteraction();
};

