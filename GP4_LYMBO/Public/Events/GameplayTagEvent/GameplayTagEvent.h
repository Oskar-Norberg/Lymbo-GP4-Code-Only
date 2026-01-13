// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameplayTagEvent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class GP4_LYMBO_API UGameplayTagEvent : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EventData")
	FGameplayTagContainer GameplayTagContainer;
};
