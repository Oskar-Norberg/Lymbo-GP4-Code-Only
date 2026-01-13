// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/States/EntityStateBase.h"
#include "Player/MainCharacter.h"
#include "PlayerStateBase.h"
#include "PlayerWalkingState.generated.h"

/**
 * 
 */

UCLASS()
class GP4_LYMBO_API UPlayerWalkingState : public UPlayerStateBase
{
	GENERATED_BODY()

public:
	UPlayerWalkingState(const FObjectInitializer& ObjectInitializer) : UPlayerStateBase(ObjectInitializer){}
	void InitPlayerState(UStateMachineBase* OwnerStateMachine, bool* bStateMachineBoolToBeUpdated,
		UCharacterMovementComponent* CharacterMovement) override;
	void EnterState() override;
	void UpdateState(float DeltaTime) override;
	void ExitState() override;

protected:
	UFUNCTION()
	void OnLanded(const FHitResult& Hit);
private:
	UPROPERTY()
	//TObjectPtr<AMainCharacterController> m_PlayerController;
	FVector m_MovementVector = FVector::ZeroVector;

};
