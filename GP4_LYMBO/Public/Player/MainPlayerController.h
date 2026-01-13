#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"


UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ToggleAutoManageActiveCameraTarget(bool SomeToggle);
};


