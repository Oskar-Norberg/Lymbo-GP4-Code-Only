// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/FormattableDataGetter.h"
#include "Systems/Dialogue/Nodes/StatementNode.h"
#include "SingleFormattableStatement.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API USingleFormattableStatement : public UStatementNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Dialogue/Formattable")
	TObjectPtr<UFormattableDataGetter> DataGetter = nullptr;

public:
	virtual FDialogueResult GetResult(const FGameDialogueContext& DialogueContext) override;
};
