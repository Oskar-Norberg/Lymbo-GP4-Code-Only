#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Systems/Interactions/InteractionBase.h"
#include "Systems/Interactions/UniversalInteractionSubsystemData.h"
#include "UObject/Object.h"
#include "UniversalInteractionSubsystem.generated.h"

UCLASS()
class GP4_LYMBO_API UUniversalInteractionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UInteractionBase* DefaultInteractionInstance = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, UInteractionBase*> InteractionMap;

	UPROPERTY(BlueprintReadOnly)
	UUniversalInteractionSubsystemData* UniversalInteractionSubsystemData = nullptr;

protected:
	void InitializeMap();

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	UInteractionBase* GetInteraction(FGameplayTag InteractionTag);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	UInteractionBase* GetDefaultInteraction();
};



