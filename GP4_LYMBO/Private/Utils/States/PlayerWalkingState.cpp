// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/States/PlayerWalkingState.h"

void UPlayerWalkingState::InitPlayerState(UStateMachineBase* OwnerStateMachine, bool* bPlayerStateMachineBoolToBeUpdated,
                                    UCharacterMovementComponent* CharacterMovement)
{
	Super::InitPlayerState(OwnerStateMachine, bPlayerStateMachineBoolToBeUpdated, CharacterMovement);
	//m_PlayerController = Cast<AMainCharacterController>(Cast<ACharacter>(m_StateMachineObjectOwner)->GetController());
	//m_PlayerStateMachineOwner->LandedDelegate.AddDynamic(this, &UPlayerRunningState::OnLanded);
}

void UPlayerWalkingState::EnterState()
{
	Super::EnterState();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Walking State")));
}

void UPlayerWalkingState::UpdateState(float DeltaTime)
{
	Super::UpdateState(DeltaTime);
	//m_PlayerStateMachineOwner->MovePlayer();
}

void UPlayerWalkingState::ExitState()
{
	Super::ExitState();
}

void UPlayerWalkingState::OnLanded(const FHitResult& Hit)
{
	//m_PlayerStateMachineOwner->GetGameState()->GetDelegateData()->GetOnPlayerLandedDelegate()->Broadcast();
}