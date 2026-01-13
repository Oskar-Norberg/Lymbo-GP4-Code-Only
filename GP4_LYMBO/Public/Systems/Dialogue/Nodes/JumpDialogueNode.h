// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "JumpDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UJumpDialogueNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue/Jump")
	FString TargetLabel;

public:
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
