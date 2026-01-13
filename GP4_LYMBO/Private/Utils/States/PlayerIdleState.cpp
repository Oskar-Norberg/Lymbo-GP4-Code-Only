// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/States/PlayerIdleState.h"

void UPlayerIdleState::EnterState()
{
	Super::EnterState();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("Idle State")));
}

void UPlayerIdleState::ExitState()
{
	Super::ExitState();
}