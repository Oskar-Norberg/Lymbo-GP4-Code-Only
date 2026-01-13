// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AnimationGestureDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GP4_LYMBO_API UAnimationGestureDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Animation Gestures")
	FString GetGestureKeyName(const FGameplayTag GameplayTag)
	{
		return Gestures.Contains(GameplayTag) ? Gestures[GameplayTag] : FString();
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Gestures")
	TMap<FGameplayTag, FString> Gestures;
};
