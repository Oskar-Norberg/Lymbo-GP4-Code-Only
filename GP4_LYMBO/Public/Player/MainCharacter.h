// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UPlayerStateBase;
class UCharacterStateMachine;
class AQuestItemScript;
class AQuestItemSocket;

UENUM(BlueprintType)
enum class EPlayerStates : uint8
{
	Idle,
	Walking,
	Running,
	Jumping,
	Dying,
	QuestMode
};

UCLASS()
class GP4_LYMBO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AQuestItemScript* PickedUpItem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AQuestItemSocket* ClosestSocket = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ClosestItem = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInRangeToSocket = false;
	
	float ClosestDistance = 0.0f;
	float MinDistanceToPickUpItem = 200.0f;

	UPROPERTY(BlueprintReadOnly)
	UCharacterStateMachine* CharacterStateMachine = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UPlayerStateBase* CurrentPlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRunning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsWalking= false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDying = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHeightUntilRespawn = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void ActivateQuestModeState() const;

	UFUNCTION(BlueprintCallable)
	void DeactivateQuestModeState() const;

	//Should be able to pick up item/ press E?
	UFUNCTION(BlueprintCallable)
	bool AbleToPickUpItem();
	
	//Should Drop item
	UFUNCTION(BlueprintCallable)
	bool TryToPickUpItem();
	
	//Should Pick up item
	UFUNCTION(BlueprintCallable)
	 bool TryToInsertItemIntoSocket();
	
	//Should Place down item into Socket
	UFUNCTION(BlueprintCallable)
	void DropItemInHand();

	UFUNCTION(BlueprintCallable)
	void PickUpItemToHand();

	UFUNCTION(BlueprintCallable)
	void InsertItemIntoSocket();
	
	//Should Place down item into Socket
	void GetClosestItem(AActor* InActor);
};
