// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/States/PlayerQuestModeState.h"

void UPlayerQuestModeState::EnterState()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::Printf(TEXT("QuestMode State")));
	Super::EnterState();
}

void UPlayerQuestModeState::ExitState()
{
	Super::ExitState();
}