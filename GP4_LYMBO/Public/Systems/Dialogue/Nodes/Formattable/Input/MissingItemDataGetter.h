// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormattableDataGetter.h"
#include "GameplayTagContainer.h"
#include "MissingItemDataGetter.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UMissingItemDataGetter : public UFormattableDataGetter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer ItemTags;

public:
	virtual FText GetText(const FGameDialogueContext& DialogueContext) const override;
};
