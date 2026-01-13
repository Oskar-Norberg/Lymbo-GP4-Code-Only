// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ProgressionSubsystem.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdded, FGameplayTag, Tag);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, FGameplayTag, Tag);

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UProgressionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// BAD CODE
public:
	UFUNCTION(BlueprintCallable, Category="Progression")
	void ResetProgression()
	{
		Tags.Reset();
	}

public:
	UFUNCTION(BlueprintCallable, Category="Progression")
	bool HasTag(const FGameplayTag& Tag) const
	{
		return Tags.HasTag(Tag);
	}

	UFUNCTION(BlueprintCallable, Category="Progression")
	bool HasAllTags(const FGameplayTagContainer& SomeTags) const
	{
		return Tags.HasAll(SomeTags);
	}

	UFUNCTION(BlueprintCallable, Category="Progression")
	void AddTag(const FGameplayTag& Tag)
	{
		Tags.AddTag(Tag);
		OnTagAdded.Broadcast(Tag);
	}

	UFUNCTION(BlueprintCallable, Category="Progression")
	void AddTags(const FGameplayTagContainer& TagsToAdd)
	{
		Tags.AppendTags(TagsToAdd);
	}

	UFUNCTION(BlueprintCallable, Category="Progression")
	void RemoveTag(const FGameplayTag& Tag)
	{
		Tags.RemoveTag(Tag);
		OnTagRemoved.Broadcast(Tag);
	}

	UFUNCTION(BlueprintCallable, Category="Progression")
	void RemoveTags(const FGameplayTagContainer& TagsToRemove)
	{
		Tags.RemoveTags(TagsToRemove);
	}

	UFUNCTION(BlueprintCallable, Category="Progression")
	void ClearTags()
	{
		Tags.Reset();
	}

public:
	UPROPERTY(BlueprintAssignable, Category="Progression")
	FOnTagAdded OnTagAdded;

	UPROPERTY(BlueprintAssignable, Category="Progression")
	FOnTagRemoved OnTagRemoved;
	
private:
	FGameplayTagContainer Tags;
};
