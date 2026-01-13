// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "PlayerQuestModeState.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UPlayerQuestModeState : public UPlayerStateBase
{
	GENERATED_BODY()
	
	virtual void EnterState() override;
	virtual void ExitState() override;
};
