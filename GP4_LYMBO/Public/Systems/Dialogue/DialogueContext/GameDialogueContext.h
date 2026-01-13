#pragma once

#include "CoreMinimal.h"
#include "GameDialogueContext.generated.h"

class IDialogueDataInterface;
class UDialogueSystemInterface;

USTRUCT(BlueprintType)
struct FGameDialogueContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<UDialogueSystemInterface> DialogueSystem = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IDialogueDataInterface> DialogueDataSystem = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWorld> World = nullptr;
};
