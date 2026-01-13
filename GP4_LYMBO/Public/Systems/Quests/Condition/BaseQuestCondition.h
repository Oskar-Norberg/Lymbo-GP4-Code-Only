// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// TODO: This should absolutely not be dependant on the WorldEventBus
#include "Subsystem/World/WorldEventBus.h"
#include "Systems/Quests/QuestConditionInterface.h"
#include "UObject/Object.h"
#include "BaseQuestCondition.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class GP4_LYMBO_API UBaseQuestCondition : public UObject, public IQuestConditionInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest Condition")
	FString ConditionName;

	UPROPERTY(BlueprintAssignable, Category="Quest Condition")
	FOnQuestConditionMet OnConditionMet;

public:
	virtual FString GetConditionName() const override;
	virtual FOnQuestConditionMet& GetOnConditionMetHandle() override;

public:
	UFUNCTION(BlueprintCallable, Category="Quest Condition")
	virtual UWorld* GetWorld() const override;

	// TODO: I absolutely DESPISE this being here, but blueprint function libraries can't be called through stupid uobjects
protected:
	UFUNCTION(BlueprintCallable, Category="Quest Condition")
	UWorldEventBus* GetQuestWorldEventBus(const AController* Controller) const;

protected:
	// Mainly a Blueprint Helper
	UFUNCTION(BlueprintCallable, Category="Quest Condition")
	void BroadcastConditionMet();

	UFUNCTION(BlueprintCallable, Category="Quest Condition")
	UWorld* GetConditionWorld() const;

	UFUNCTION(BlueprintCallable, Category="Quest Condition")
	UObject* GetConditionOwner() const;
};
