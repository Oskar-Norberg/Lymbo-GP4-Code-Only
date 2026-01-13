// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/States/PlayerStateBase.h"
#include "Utils/StateMachines/CharacterStateMachine.h"

void UPlayerStateBase::InitPlayerState(UStateMachineBase* StateMachine, bool* bPlayerStateMachineBoolToBeUpdated,
	UCharacterMovementComponent* CharacterMovement)
{
	Super::InitState(StateMachine, StateMachine->GetOwner(), bPlayerStateMachineBoolToBeUpdated);
	m_PlayerStateMachine = Cast<UCharacterStateMachine>(StateMachine);
	m_PlayerStateMachineOwner = Cast<AMainCharacter>(m_StateMachine->GetOwner());
	m_CharacterMovement = CharacterMovement;
}

void UPlayerStateBase::EnterState()
{
	Super::EnterState();
}

void UPlayerStateBase::ExitState()
{
	Super::ExitState();
}