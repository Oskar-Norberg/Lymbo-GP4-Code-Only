// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "PlayerIdleState.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UPlayerIdleState : public UPlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void EnterState() override;
	virtual void ExitState() override;
};
