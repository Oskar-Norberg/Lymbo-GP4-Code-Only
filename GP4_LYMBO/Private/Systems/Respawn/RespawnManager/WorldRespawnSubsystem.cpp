// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Respawn/RespawnManager/WorldRespawnSubsystem.h"

void UWorldRespawnSubsystem::RespawnPlayer()
{
	if (IsValid(PlayerController) && IsValid(ActiveCheckpoint))
	{
		PlayerController->GetPawn()->SetActorLocation(ActiveCheckpoint->GetRespawnLocation());
	}
	else
	{
		if (!IsValid(PlayerController))
			UE_LOG(LogTemp, Error, TEXT("PlayerController is invalid"));

		if (!IsValid(ActiveCheckpoint))
			UE_LOG(LogTemp, Error, TEXT("ActiveCheckpoint is invalid"));
	}
	OnPlayerRespawned.Broadcast();
	RespawnInProgress = false;
}

void UWorldRespawnSubsystem::StartPlayerRespawn()
{
	if (IsValid(PlayerController))
	{
		if (IsValid(ActiveCheckpoint))
		{
			if (PlayerController->GetPawn().GetClass()->ImplementsInterface(URespawnable::StaticClass())
				&& !RespawnInProgress)
			{
				RespawnInProgress = true;
				IRespawnable::Execute_StartRespawn(PlayerController->GetPawn());
			}
			
			else
			{
				UE_LOG(LogTemp, Error, TEXT("PlayerController dose not implement [Respawnable] interface"));
			}
		}
		
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ActiveCheckpoint is invalid"));
		}
	}
	
	else
	{
		//print error
		UE_LOG(LogTemp, Error, TEXT("PlayerController is invalid"));
	}
}

void UWorldRespawnSubsystem::SetCheckpoint(ACheckpoint* checkpoint)
{
	ActiveCheckpoint = checkpoint;
	
	OnSetNewCheckpoint.Broadcast();
}

void UWorldRespawnSubsystem::SetPlayerController(AController* pcontroller)
{
	PlayerController = pcontroller;
}

ACheckpoint* UWorldRespawnSubsystem::GetActiveCheckpoint()
{
	return ActiveCheckpoint;
}
