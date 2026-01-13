// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Dialogue/DialogueContext/GameDialogueContext.h"
#include "UObject/Object.h"
#include "FormattableDataGetter.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class GP4_LYMBO_API UFormattableDataGetter : public UObject
{
	GENERATED_BODY()

public:
	virtual FText GetText(const FGameDialogueContext& DialogueContext) const PURE_VIRTUAL(UFormattableDataGetter::GetText, return FText::GetEmpty(););
};
