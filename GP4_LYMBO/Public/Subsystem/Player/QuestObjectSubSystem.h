// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EQuestItemType : uint8
{
	Character,
	Object
};

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "QuestObjectSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UQuestObjectSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable)
	bool AreQuestSocketsInUse(const TArray<int32>& Ints);

	UFUNCTION(BlueprintCallable)
	void FreezeTheseQuestSockets(const TArray<int32>& Ints);

	UFUNCTION(BlueprintCallable)
	void UnFreezeTheseQuestSockets(const TArray<int32>& Ints);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*>  GetQuestSocketsActor(const TArray<int32>& QuestSocketIndexes);

	UFUNCTION(BlueprintCallable)
	AActor* GetQuestSocketActor(const int32& QuestSocketIndex);

	UFUNCTION(BlueprintCallable)
	bool GetIfSocketsHaveCorrectActor(TArray<FString> WhichNames, const TArray<int32>& QuestSocketIndexes);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CurrentQuestPart = 1;
};
