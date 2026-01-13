// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/Quests/Condition/BaseQuestCondition.h"
#include "UWaitCondition.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UWaitCondition : public UBaseQuestCondition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest Condition", meta=(Units="ms", ClampMin="0.0"))
	float WaitTime;

public:
	virtual void InitCondition_Implementation(const AController* QuestInstigator) override;

private:
	FTimerHandle WaitTimer;

private:
	void HandleWaitTimerFinished();
};
