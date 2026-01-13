// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Player/DialogueSubsystem.h"

#include "Systems/Dialogue/System/DialogueDataSystem.h"

void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DialogueSystem = NewObject<UDialogueSystem>(this, UDialogueSystem::StaticClass());
	checkf(DialogueSystem, TEXT("UDialogueSubsystem::Initialize: Failed to create DialogueSystem"));

	DialogueDataSystem = NewObject<UDialogueDataSystem>(this, UDialogueDataSystem::StaticClass());
	checkf(DialogueSystem, TEXT("UDialogueSubsystem::Initialize: Failed to create DialogueDataSystem"));

	// Managing both of these here ensure they will never go stale
	DialogueSystem->SetDialogueDataSystem(DialogueDataSystem);

	DialogueSystem->GetOnDialogueSetHandle().AddDynamic(this, &UDialogueSubsystem::HandleOnDialogueSet);
	DialogueSystem->GetOnDialogueInitiatedHandle().AddDynamic(this, &UDialogueSubsystem::HandleOnDialogueInitiated);
	DialogueSystem->GetOnDialogueProgressedHandle().AddDynamic(this, &UDialogueSubsystem::HandleOnDialogueProgressed);
	DialogueSystem->GetOnDialogueExitedHandle().AddDynamic(this, &UDialogueSubsystem::HandleOnDialogueExited);
}

void UDialogueSubsystem::ResetDialogueSystem()
{
	DialogueDataSystem = NewObject<UDialogueDataSystem>(this, UDialogueDataSystem::StaticClass());
	checkf(DialogueSystem, TEXT("UDialogueSubsystem::Initialize: Failed to create DialogueDataSystem"));
	DialogueSystem->SetDialogueDataSystem(DialogueDataSystem);
	DialogueSystem->ResetDialogueSystem();
}

void UDialogueSubsystem::InitiateDialogue(UDialogueDataAsset* SomeDialogueAsset, APlayerController* PlayerController)
{
	DialogueSystem->InitiateDialogue(SomeDialogueAsset, PlayerController);
}

void UDialogueSubsystem::ExitDialogue()
{
	OnDialogueExited.Broadcast();
}

FDialogueResult UDialogueSubsystem::ProgressDialogue()
{
	const auto DialogueResult = DialogueSystem->ProgressDialogue();
	OnDialogueProgressed.Broadcast(DialogueResult);
	return DialogueResult;
}

void UDialogueSubsystem::SelectOption(int OptionIndex)
{
	return DialogueSystem->SelectOption(OptionIndex);
}

FOnDialogueSet& UDialogueSubsystem::GetOnDialogueSetHandle()
{
	return OnDialogueSet;
}

FOnDialogueInitiated& UDialogueSubsystem::GetOnDialogueInitiatedHandle()
{
	return OnDialogueInitiated;
}

FOnDialogueProgressed& UDialogueSubsystem::GetOnDialogueProgressedHandle()
{
	return OnDialogueProgressed;
}

FOnDialogueExited& UDialogueSubsystem::GetOnDialogueExitedHandle()
{
	return OnDialogueExited;
}

void UDialogueSubsystem::HandleOnDialogueSet()
{
	OnDialogueSet.Broadcast();
}

void UDialogueSubsystem::HandleOnDialogueInitiated()
{
	OnDialogueInitiated.Broadcast();
}

void UDialogueSubsystem::HandleOnDialogueProgressed(FDialogueResult DialogueResult)
{
	OnDialogueProgressed.Broadcast(DialogueResult);
}

void UDialogueSubsystem::HandleOnDialogueExited()
{
	OnDialogueExited.Broadcast();
}

bool UDialogueSubsystem::TryGetBool(const FString& Key, bool& OutValue) const
{
	return DialogueDataSystem->TryGetBool(Key, OutValue);
}

void UDialogueSubsystem::SetBool(const FString& Key, const bool Value)
{
	DialogueDataSystem->SetBool(Key, Value);
}

bool UDialogueSubsystem::TryGetString(const FString& Key, FString& OutValue) const
{
	return DialogueDataSystem->TryGetString(Key, OutValue);
}

void UDialogueSubsystem::SetString(const FString& Key, const FString& Value)
{
	DialogueDataSystem->SetString(Key, Value);
}

bool UDialogueSubsystem::TryGetInt(const FString& Key, int& OutValue) const
{
	return DialogueDataSystem->TryGetInt(Key, OutValue);
}

void UDialogueSubsystem::SetInt(const FString& Key, const int Value)
{
	DialogueDataSystem->SetInt(Key, Value);
}
