#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TeleportInitiator.generated.h"

UINTERFACE()
class UTeleportInitiator : public UInterface
{
	GENERATED_BODY()
};

class ITeleportInitiator
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	const AActor* GetTeleportLocationActor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	const UClass* GetGraphicsPresetChangeOnTeleport();
};

