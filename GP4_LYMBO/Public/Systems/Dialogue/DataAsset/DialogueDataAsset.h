// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Systems/Dialogue/Nodes/DialogueNodeBase.h"
#include "DialogueDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Dialogue")
	TArray<TObjectPtr<UDialogueNodeBase>> Nodes;
};
