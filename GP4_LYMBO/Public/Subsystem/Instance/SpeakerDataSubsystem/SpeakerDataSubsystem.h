// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/SpeakersDataAsset.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SpeakerDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API USpeakerDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Speakers")
	FText GetSpeakerNameByTag(FGameplayTag SpeakerTag) const;

	UFUNCTION(BlueprintCallable, Category = "Speakers")
	FSpeakerSoundData GetSpeakerSoundDataByTag(FGameplayTag SpeakerTag) const;

private:
	UPROPERTY()
	TObjectPtr<USpeakersDataAsset> SpeakersDataAsset;
};
