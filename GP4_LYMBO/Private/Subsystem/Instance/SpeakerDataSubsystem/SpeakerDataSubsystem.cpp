// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Instance/SpeakerDataSubsystem/SpeakerDataSubsystem.h"

#include "Core/Instance/LymboGameInstance.h"

void USpeakerDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const auto* GameInstance = Cast<ULymboGameInstance>(GetWorld()->GetGameInstance());
	checkf(GameInstance, TEXT("USpeakerDataSubsystem::Initialize ULymboGameInstance is null!"));
	checkf(GameInstance->SpeakersDataAsset, TEXT("USpeakerDataSubsystem::Initialize SpeakersDataAsset is null!"));

	SpeakersDataAsset = GameInstance->SpeakersDataAsset;
}

FText USpeakerDataSubsystem::GetSpeakerNameByTag(const FGameplayTag SpeakerTag) const
{
	if (const auto* FoundSpeaker = SpeakersDataAsset->Speakers.Find(SpeakerTag))
	{
		return FoundSpeaker->SpeakerName;
	}

	return FText::GetEmpty();
}

FSpeakerSoundData USpeakerDataSubsystem::GetSpeakerSoundDataByTag(const FGameplayTag SpeakerTag) const
{
	if (const auto* FoundSpeaker = SpeakersDataAsset->Speakers.Find(SpeakerTag))
	{
		return FoundSpeaker->SpeakingSoundData;
	}

	return {};
}
