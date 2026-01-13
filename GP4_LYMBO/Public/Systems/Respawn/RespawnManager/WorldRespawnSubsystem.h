// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Respawnable.h"
#include "Subsystems/WorldSubsystem.h"
#include "Systems/Interactions/Interaction_Interface.h"
#include "Systems/Respawn/Checkpoints/Checkpoint.h"
#include "WorldRespawnSubsystem.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetNewCheckpoint);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerRespawned);


UCLASS()
class GP4_LYMBO_API UWorldRespawnSubsystem : public UWorldSubsystem, public IRespawnable
{
	GENERATED_BODY()
private:

	UPROPERTY()
	ACheckpoint* ActiveCheckpoint = nullptr;

	UPROPERTY()
	AController* PlayerController = nullptr;

	bool RespawnInProgress = false;
	
public:

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();
	
	UFUNCTION(BlueprintCallable)
	void StartPlayerRespawn();

	UFUNCTION(BlueprintCallable)
	void SetCheckpoint(ACheckpoint* checkpoint);

	UFUNCTION(BlueprintCallable)
	void SetPlayerController(AController* pcontroller);
	
	UFUNCTION(BlueprintCallable)
	ACheckpoint* GetActiveCheckpoint();

	
	UPROPERTY(BlueprintAssignable)
	FOnSetNewCheckpoint OnSetNewCheckpoint;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerRespawned OnPlayerRespawned;
};
