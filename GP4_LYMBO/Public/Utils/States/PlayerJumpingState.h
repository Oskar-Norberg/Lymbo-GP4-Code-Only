// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "PlayerJumpingState.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UPlayerJumpingState : public UPlayerStateBase
{
	GENERATED_BODY()

public:
	UPlayerJumpingState(const FObjectInitializer& ObjectInitializer) : UPlayerStateBase(ObjectInitializer){}
	virtual void InitPlayerState(UStateMachineBase* StateMachine, bool* bPlayerStateMachineBoolToBeUpdated, UCharacterMovementComponent* CharacterMovement) override;
	void EnterState() override;
	virtual void UpdateState(float DeltaTime) override;
	void ExitState() override;

protected:
	UFUNCTION()
	void OnJumpEnded(const FHitResult& Hit);
};
