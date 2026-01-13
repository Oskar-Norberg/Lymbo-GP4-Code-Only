#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Systems/Dialogue/Animation/DialogueAnimationData.h"
#include "FDialogueResult.generated.h"

UENUM(BlueprintType)
enum class EDialogueFlowType : uint8
{
	Continue UMETA(DisplayName = "Continue"),
	Jump UMETA(DisplayName = "Jump"),
	End UMETA(DisplayName = "End"),
};

UENUM(BlueprintType)
enum class EDialogueResultType : uint8
{
	None UMETA(DisplayName = "None"),
	Statement UMETA(DisplayName = "Statement"),
	Option UMETA(DisplayName = "Option"),
};

// TODO: Ask designers if options can be locked.
USTRUCT(BlueprintType)
struct FOptionsData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue/Options")
	FText Text = FText::GetEmpty();
};

USTRUCT(BlueprintType)
struct FDialogueResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue/Type")
	EDialogueFlowType FlowType = EDialogueFlowType::End;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue/Type")
	EDialogueResultType Type = EDialogueResultType::None;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	FGameplayTag SpeakerTag = FGameplayTag::EmptyTag;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	bool DoCloseDialogue = true;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	bool ForceClose = false;

	// For Statement type
	// ------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	FText Text = FText::GetEmpty();
	// ------------------------------------------------

	// For Option type
	// ------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue/Options")
	TArray<FOptionsData> Options;
	// ------------------------------------------------

	// For Jump type
	// ------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue/Jump")
	FString TargetLabel = FString();
	// ------------------------------------------------


	// For playing animations
	// ------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue/Animation")
	TArray<FDialogueAnimationData> AnimationTags;
	// ------------------------------------------------
};
