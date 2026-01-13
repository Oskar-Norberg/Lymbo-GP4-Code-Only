// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueDataInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDialogueDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GP4_LYMBO_API IDialogueDataInterface
{
	GENERATED_BODY()

public:
	virtual bool TryGetBool(const FString& Key, bool& OutValue) const = 0;
	virtual void SetBool(const FString& Key, bool Value) = 0;

public:
	virtual bool TryGetString(const FString& Key, FString& OutValue) const = 0;
	virtual void SetString(const FString& Key, const FString& Value) = 0;

public:
	virtual bool TryGetInt(const FString& Key, int& OutValue) const = 0;
	virtual void SetInt(const FString& Key, int Value) = 0;
};
