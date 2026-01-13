// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/StateMachines/CharacterStateMachine.h"
#include "Utils/StateMachines/StateMachineBase.h"
#include "Utils/StateMachines/CharacterStateMachine.h"

#include "Utils/States/PlayerDeadState.h"
#include "Utils/States/PlayerIdleState.h"
#include "Utils/States/PlayerJumpingState.h"
#include "Utils/States/PlayerRunningState.h"
#include "Utils/States/PlayerStateBase.h"
#include "Utils/States/PlayerWalkingState.h"
#include "Utils/States/PlayerQuestModeState.h"

void UCharacterStateMachine::InitStateMachine(AActor* Owner)
{
	Super::InitStateMachine(Owner);
	m_PlayerOwner = Cast<AMainCharacter>(Owner);
	AddStates();
	m_CurrentState = m_StateObjects[UPlayerIdleState::StaticClass()];
	m_CurrentState->EnterState();
}

void UCharacterStateMachine::AddStates()
{
	Super::AddStates();
	InitializeNewState(UPlayerIdleState::StaticClass(), &m_bIsIdle, m_PlayerOwner->GetCharacterMovement());
	InitializeNewState(UPlayerRunningState::StaticClass(), &m_bIsRunning, m_PlayerOwner->GetCharacterMovement());
	InitializeNewState(UPlayerJumpingState::StaticClass(), &m_bIsJumping, m_PlayerOwner->GetCharacterMovement());
	InitializeNewState(UPlayerDeadState::StaticClass(), &m_bIsDead, m_PlayerOwner->GetCharacterMovement());
	InitializeNewState(UPlayerWalkingState::StaticClass(), &m_bisWalking, m_PlayerOwner->GetCharacterMovement());
	InitializeNewState(UPlayerQuestModeState::StaticClass(), &m_bIsInQuestMode, m_PlayerOwner->GetCharacterMovement());
}

void UCharacterStateMachine::InitializeNewState(UClass* StateClass, bool* bPlayerStateMachineBoolToBeUpdated,
	UCharacterMovementComponent* CharacterMovement)
{
	UPlayerStateBase* NewState = NewObject<UPlayerStateBase>(this, StateClass);
	NewState->InitPlayerState(this, bPlayerStateMachineBoolToBeUpdated, CharacterMovement);
	m_StateObjects.Add(StateClass, NewState);
}

bool UCharacterStateMachine::GetIsIdle()
{
	return m_bIsIdle;
}

bool UCharacterStateMachine::GetIsRunning()
{
	return m_bIsRunning;
}

bool UCharacterStateMachine::GetIsJumping()
{
	return m_bIsJumping;
}

bool UCharacterStateMachine::GetIsDead()
{
	return m_bIsDead;
}

bool UCharacterStateMachine::GetIsKicking()
{
	return m_bIsKicking;
}

bool UCharacterStateMachine::GetIsWalking()
{
	return m_bisWalking;
}

bool UCharacterStateMachine::GetIsInQuestMode()
{
	return m_bIsInQuestMode;
}

AMainCharacter* UCharacterStateMachine::GetPlayerOwner()
{
	return m_PlayerOwner;
}

void UCharacterStateMachine::ChangeState(EPlayerStates TheNewState)
{
	m_CurrentState->ExitState();
	switch (TheNewState)
	{
		case EPlayerStates::Idle: m_CurrentState = m_StateObjects[UPlayerIdleState::StaticClass()]; break;
		case EPlayerStates::Walking: m_CurrentState = m_StateObjects[UPlayerWalkingState::StaticClass()]; break;
		case EPlayerStates::Running: m_CurrentState = m_StateObjects[UPlayerRunningState::StaticClass()]; break;
		case EPlayerStates::Jumping: m_CurrentState = m_StateObjects[UPlayerJumpingState::StaticClass()]; break;
		case EPlayerStates::Dying: m_CurrentState = m_StateObjects[UPlayerDeadState::StaticClass()]; break;
		case EPlayerStates::QuestMode: m_CurrentState = m_StateObjects[UPlayerQuestModeState::StaticClass()]; break;
		default: m_CurrentState = m_StateObjects[UPlayerIdleState::StaticClass()]; break;
	}
	m_CurrentState->EnterState();
}