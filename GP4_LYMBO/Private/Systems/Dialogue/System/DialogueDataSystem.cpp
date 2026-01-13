// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Dialogue/System/DialogueDataSystem.h"

bool UDialogueDataSystem::TryGetBool(const FString& Key, bool& OutValue) const
{
	if (const auto* Found = BoolData.Find(Key))
	{
		OutValue = *Found;
		return true;
	}

	return false;
}

void UDialogueDataSystem::SetBool(const FString& Key, const bool Value)
{
	BoolData.Add(Key, Value);
}

bool UDialogueDataSystem::TryGetString(const FString& Key, FString& OutValue) const
{
	if (const auto* Found = StringData.Find(Key))
	{
		OutValue = *Found;
		return true;
	}

	return false;
}

void UDialogueDataSystem::SetString(const FString& Key, const FString& Value)
{
	StringData.Add(Key, Value);
}

bool UDialogueDataSystem::TryGetInt(const FString& Key, int& OutValue) const
{
	if (const auto* Found = IntData.Find(Key))
	{
		OutValue = *Found;
		return true;
	}

	return false;
}

void UDialogueDataSystem::SetInt(const FString& Key, const int Value)
{
	IntData.Add(Key, Value);
}
