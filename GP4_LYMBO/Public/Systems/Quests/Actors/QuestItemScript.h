// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystem/Player/QuestObjectSubSystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestItemScript.generated.h"

UCLASS()
class GP4_LYMBO_API AQuestItemScript : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestItemScript();

UPROPERTY(EditAnywhere, BlueprintReadWrite)
EQuestItemType QuestItemType = EQuestItemType::Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestItemName = " ";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator CustomRotation = FRotator();

	UPROPERTY(BlueprintReadWrite)
	bool IsPickedUp = false;

	UPROPERTY(BlueprintReadOnly)
	FTransform InitTransform = FTransform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float  MaximumDistanceUntilRespawn = 0.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
