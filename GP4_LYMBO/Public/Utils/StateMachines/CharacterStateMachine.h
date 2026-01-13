// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/StateMachines/StateMachineBase.h"
#include "Player/MainCharacter.h"
#include "CharacterStateMachine.generated.h"


/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UCharacterStateMachine : public UStateMachineBase
{
	GENERATED_BODY()

private:
	bool m_bIsIdle = false;
	bool m_bIsRunning = false;
	bool m_bisWalking = false;
	bool m_bIsKicking = false;
	bool m_bIsJumping = false;
	bool m_bIsDead = false;
	bool m_bIsInQuestMode = false;

protected:
	virtual void AddStates() override;
	void InitializeNewState(UClass* StateClass, bool* bPlayerStateMachineBoolToBeUpdated, UCharacterMovementComponent* CharacterMovement);

	UPROPERTY()
	TObjectPtr<AMainCharacter> m_PlayerOwner;

public:
	UCharacterStateMachine(const FObjectInitializer& ObjectInitializer) : UStateMachineBase(ObjectInitializer){}
	virtual void InitStateMachine(AActor* Owner) override;
	UFUNCTION(BlueprintCallable)
	bool GetIsIdle();
	UFUNCTION(BlueprintCallable)
	bool GetIsRunning();
	UFUNCTION(BlueprintCallable)
	bool GetIsJumping();
	UFUNCTION(BlueprintCallable)
	bool GetIsDead();
	UFUNCTION(BlueprintCallable)
	bool GetIsKicking();
	UFUNCTION(BlueprintCallable)
	bool GetIsWalking();
	UFUNCTION(BlueprintCallable)
	bool GetIsInQuestMode();
	UFUNCTION(BlueprintCallable)
	AMainCharacter* GetPlayerOwner();

void ChangeState(EPlayerStates TheNewState);
};
