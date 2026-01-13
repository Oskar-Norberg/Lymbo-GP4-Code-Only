// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SpeakersDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FSpeakerSoundData
{
	GENERATED_BODY()

	// This really ought to be a TSoftObjectPtr, but I cannot be bothered to load the asset asynchronously.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaker")
	TObjectPtr<USoundBase> SpeakerSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaker")
	float TimePerRepeat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaker", meta=(ClampMin=0.0f))
	float MinPitch = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaker", meta=(ClampMin=0.0f))
	float MaxPitch = 1.0f;
};

USTRUCT(BlueprintType)
struct FSpeakerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaker")
	FText SpeakerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaker")
	FSpeakerSoundData SpeakingSoundData;
};

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API USpeakersDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speakers")
	TMap<FGameplayTag, FSpeakerInfo> Speakers;
};
