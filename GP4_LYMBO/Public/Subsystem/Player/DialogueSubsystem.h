// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Systems/Dialogue/Data/DialogueDataInterface.h"
#include "Systems/Dialogue/System/DialogueSystem.h"
#include "DialogueSubsystem.generated.h"

class UDialogueDataSystem;
/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UDialogueSubsystem : public ULocalPlayerSubsystem, public IDialogueSystemInterface,
                                         public IDialogueDataInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// BAD CODE 
public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ResetDialogueSystem();
	
	// IDialogueSystemInterface
	// -----------------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual void InitiateDialogue(UDialogueDataAsset* SomeDialogueAsset, APlayerController* PlayerController) override;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual FDialogueResult ProgressDialogue() override;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual void ExitDialogue() override;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	virtual void SelectOption(int OptionIndex) override;

public:
	virtual FOnDialogueSet& GetOnDialogueSetHandle() override;
	virtual FOnDialogueInitiated& GetOnDialogueInitiatedHandle() override;
	virtual FOnDialogueProgressed& GetOnDialogueProgressedHandle() override;
	virtual FOnDialogueExited& GetOnDialogueExitedHandle() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Dialogue/Events")
	FOnDialogueSet OnDialogueSet;
	UPROPERTY(BlueprintAssignable, Category = "Dialogue/Events")
	FOnDialogueInitiated OnDialogueInitiated;
	UPROPERTY(BlueprintAssignable, Category = "Dialogue/Events")
	FOnDialogueProgressed OnDialogueProgressed;
	UPROPERTY(BlueprintAssignable, Category = "Dialogue/Events")
	FOnDialogueExited OnDialogueExited;

private:
	UPROPERTY()
	TObjectPtr<UDialogueSystem> DialogueSystem;
	UPROPERTY()
	TObjectPtr<UDialogueDataSystem> DialogueDataSystem;

private:
	UFUNCTION()
	void HandleOnDialogueSet();
	UFUNCTION()
	void HandleOnDialogueInitiated();
	UFUNCTION()
	void HandleOnDialogueProgressed(FDialogueResult DialogueResult);
	UFUNCTION()
	void HandleOnDialogueExited();
	// -----------------------------------------------

	// IDialogueDataInterface
	// -----------------------------------------------
public:
	virtual bool TryGetBool(const FString& Key, bool& OutValue) const override;
	virtual void SetBool(const FString& Key, bool Value) override;
	virtual bool TryGetString(const FString& Key, FString& OutValue) const override;
	virtual void SetString(const FString& Key, const FString& Value) override;
	virtual bool TryGetInt(const FString& Key, int& OutValue) const override;
	virtual void SetInt(const FString& Key, int Value) override;
	// -----------------------------------------------
};
