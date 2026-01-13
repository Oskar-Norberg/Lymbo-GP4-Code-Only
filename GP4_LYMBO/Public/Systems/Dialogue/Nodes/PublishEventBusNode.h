// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeBase.h"
#include "PublishEventBusNode.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UPublishEventBusNode : public UDialogueNodeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Dialogue")
	TObjectPtr<UObject> EventData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	bool DoForceClose = false; 

public:
	virtual void ExecuteNode(FGameDialogueContext DialogueContext) override;
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
