// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Dialogue/Data/DialogueDataInterface.h"
#include "UObject/Object.h"
#include "DialogueDataSystem.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UDialogueDataSystem : public UObject, public IDialogueDataInterface
{
	GENERATED_BODY()

public:
	virtual bool TryGetBool(const FString& Key, bool& OutValue) const override;
	virtual void SetBool(const FString& Key, bool Value) override;
public:
	virtual bool TryGetString(const FString& Key, FString& OutValue) const override;
	virtual void SetString(const FString& Key, const FString& Value) override;
public:
	virtual bool TryGetInt(const FString& Key, int& OutValue) const override;
	virtual void SetInt(const FString& Key, int Value) override;

	// TODO: TVariants are annoying to work with in maps. Look into. Having three separate maps is bad.
private:
	TMap<FString, bool> BoolData;
	TMap<FString, FString> StringData;
	TMap<FString, int> IntData;
};
