// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/UserDefinedStruct.h"
#include "DialogueAnimationData.generated.h"

USTRUCT(BlueprintType)
struct FDialogueAnimationData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta=(Categories="Speaker"))
	FGameplayTag CharacterTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta=(Categories="Animation"))
	FGameplayTag AnimationTag;
};
