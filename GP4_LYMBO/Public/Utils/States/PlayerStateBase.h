// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/States/EntityStateBase.h"
#include "Player/MainCharacter.h"
#include "Utils/StateMachines/CharacterStateMachine.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */
class UCharacterStateMachine;

UCLASS()
class GP4_LYMBO_API UPlayerStateBase : public UEntityStateBase
{
	GENERATED_BODY()
public:
	UPlayerStateBase(const FObjectInitializer& ObjectInitializer) : UEntityStateBase(ObjectInitializer){}
	virtual void InitPlayerState(UStateMachineBase* StateMachine, bool* bPlayerStateMachineBoolToBeUpdated, UCharacterMovementComponent* CharacterMovement);
	virtual void EnterState() override;
	virtual void ExitState() override;
	
protected:
	UPROPERTY()
	TObjectPtr<UCharacterStateMachine> m_PlayerStateMachine;
	UPROPERTY()
	TObjectPtr<AMainCharacter> m_PlayerStateMachineOwner;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> m_CharacterMovement;
};
