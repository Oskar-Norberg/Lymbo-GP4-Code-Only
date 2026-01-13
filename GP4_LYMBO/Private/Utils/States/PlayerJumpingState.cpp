// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/States/PlayerJumpingState.h"

void UPlayerJumpingState::InitPlayerState(UStateMachineBase* StateMachine, bool* bPlayerStateMachineBoolToBeUpdated,
                                    UCharacterMovementComponent* CharacterMovement)
{
	Super::InitPlayerState(StateMachine, bPlayerStateMachineBoolToBeUpdated, CharacterMovement);
	//m_PlayerStateMachineOwner->LandedDelegate.AddDynamic(this, &UPlayerJumpingState::OnJumpEnded);
}

void UPlayerJumpingState::EnterState()
{
	Super::EnterState();
	//m_PlayerStateMachineOwner->GetGameState()->GetDelegateData()->GetOnPlayerStartedJumpingDelegate()->Broadcast();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Jumping State")));
	//m_PlayerStateMachineOwner->Jump();
}

void UPlayerJumpingState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	//m_PlayerStateMachineOwner->MovePlayer();
}

void UPlayerJumpingState::ExitState()
{
	Super::ExitState();
}

void UPlayerJumpingState::OnJumpEnded(const FHitResult& Hit)
{
	//m_PlayerStateMachineOwner->GetGameState()->GetDelegateData()->GetOnPlayerLandedDelegate()->Broadcast();
	//m_PlayerStateMachine->SwitchState(UPlayerIdleState::StaticClass());
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("EXIT JUMPING")));
}