#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Respawnable.generated.h"

UINTERFACE()
class URespawnable : public UInterface
{
	GENERATED_BODY()
};

class IRespawnable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartRespawn();
};
