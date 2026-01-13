// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AnimationDataSubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GP4_LYMBO_API UAnimationDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Animation Data")
	void SetValue(const FString& Key, const bool Value)
	{
		AnimationDataMap.Add(Key, Value);
	}

	UFUNCTION(BlueprintCallable, Category = "Animation Data")
	bool GetValue(const FString& Key)
	{
		return AnimationDataMap.Contains(Key) && AnimationDataMap[Key];
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Data")
	TMap<FString, bool> AnimationDataMap;
};
