#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IPatrollable.generated.h"

UENUM(BlueprintType)
enum EPatrollingType
{
	LOOPING,
	PING_PONG
};

UINTERFACE(BlueprintType, Blueprintable)
class UPatrollable : public UInterface
{
	GENERATED_BODY()
};

class IPatrollable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Patrolling Object")
	TArray<AActor*> GetPatrolPoints();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Patrolling Object")
	EPatrollingType GetPatrollingType();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Patrolling Object")
	TArray<FRotator> GetLookAtRotations();
};

