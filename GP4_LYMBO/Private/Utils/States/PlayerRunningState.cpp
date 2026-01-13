// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/States/PlayerRunningState.h"

void UPlayerRunningState::InitPlayerState(UStateMachineBase* OwnerStateMachine, bool* bPlayerStateMachineBoolToBeUpdated,
                                    UCharacterMovementComponent* CharacterMovement)
{
	Super::InitPlayerState(OwnerStateMachine, bPlayerStateMachineBoolToBeUpdated, CharacterMovement);
	//m_PlayerController = Cast<AMainCharacterController>(Cast<ACharacter>(m_StateMachineObjectOwner)->GetController());
	//m_PlayerStateMachineOwner->LandedDelegate.AddDynamic(this, &UPlayerRunningState::OnLanded);
}

void UPlayerRunningState::EnterState()
{
	Super::EnterState();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Running State")));
}

void UPlayerRunningState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	//m_PlayerStateMachineOwner->MovePlayer();
}

void UPlayerRunningState::ExitState()
{
	Super::ExitState();
}

void UPlayerRunningState::OnLanded(const FHitResult& Hit)
{
	//m_PlayerStateMachineOwner->GetGameState()->GetDelegateData()->GetOnPlayerLandedDelegate()->Broadcast();
}