// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/Quests/Actors/QuestItemScript.h"
#include "Systems/Quests/Actors/QuestItemSocket.h"
#include "Systems/Respawn/RespawnManager/WorldRespawnSubsystem.h"
#include  "Utils/States/PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/StateMachines/CharacterStateMachine.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterStateMachine = NewObject<UCharacterStateMachine>(this /*Outer*/);
	CharacterStateMachine->InitStateMachine(this);
	
	CurrentPlayerState = NewObject<UPlayerStateBase>(this /*Outer*/);
	bool* bPlayerStateMachineBoolToBeUpdated = { };
	CurrentPlayerState->InitPlayerState(CharacterStateMachine, bPlayerStateMachineBoolToBeUpdated, GetCharacterMovement());

	UWorldRespawnSubsystem* WorldRespawnSubsystem = GetWorld()->GetSubsystem<UWorldRespawnSubsystem>();
	ACheckpoint* SpawnCheckpoint = GetWorld()->SpawnActor<ACheckpoint>(ACheckpoint::StaticClass(), GetActorTransform());
	WorldRespawnSubsystem->SetCheckpoint(SpawnCheckpoint);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (GetActorLocation().Z <= MaxHeightUntilRespawn)
	{
		UWorldRespawnSubsystem* WorldRespawnSubsystem = GetWorld()->GetSubsystem<UWorldRespawnSubsystem>();
		WorldRespawnSubsystem->RespawnPlayer();
	}
	
	if (CharacterStateMachine->GetIsInQuestMode()) return;
	if (GetCharacterMovement()->IsFalling())
	{
		CharacterStateMachine->ChangeState(EPlayerStates::Jumping);
	}
	else if (bIsRunning)
	{
		CharacterStateMachine->ChangeState(EPlayerStates::Running);
	}
	else if (!bIsRunning && bIsWalking)
	{
		CharacterStateMachine->ChangeState(EPlayerStates::Walking);
	}
	else if (bIsDying)
	{
		CharacterStateMachine->ChangeState(EPlayerStates::Dying);
	}
	else
	{
		CharacterStateMachine->ChangeState(EPlayerStates::Idle);
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::ActivateQuestModeState() const
{
	CharacterStateMachine->ChangeState(EPlayerStates::QuestMode);
}

void AMainCharacter::DeactivateQuestModeState() const
{
	CharacterStateMachine->ChangeState(EPlayerStates::Idle);
}

//Should be able to pick up item/ press E?
bool AMainCharacter::AbleToPickUpItem()
{
	if (IsValid(PickedUpItem))
	{
		return false;
	}
	else return true;
}

bool AMainCharacter::TryToPickUpItem()
{
	TArray<AActor*> HoldInHandItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AQuestItemScript::StaticClass(), HoldInHandItems);
	if (HoldInHandItems.Num() > 0)
	{
		for(auto item : HoldInHandItems)
		{
			GetClosestItem(item);
		}
		if (IsValid(ClosestSocket))
		{
			if (ClosestSocket->SocketIsFrozen) return false;
		}
		if (GetDistanceTo(ClosestItem) <= MinDistanceToPickUpItem)
		{
			return true;
		}
	}
	return false;
}

bool AMainCharacter::TryToInsertItemIntoSocket()
{
	if (IsValid(ClosestSocket))
	{
		if (IsValid(ClosestSocket->CurrentActorInSocket))
		{
			AQuestItemScript* SocketsCastItem = Cast< AQuestItemScript>(ClosestSocket->CurrentActorInSocket);
			SocketsCastItem->SetActorTransform(SocketsCastItem->InitTransform);
		}
		return true;
		// if (ClosestSocket->CurrentActorInSocket == nullptr && IsInRangeToSocket && !ClosestSocket->SocketIsFrozen)
		// {
		// 	return true;
		// }
		// else return false; // this will drop the item
	}
	else
	{
		return false;
	}
}

//Should Drop item
void AMainCharacter::DropItemInHand()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		FVector Start = GetActorLocation() + FVector(0, 0, 50); // Slightly above ground
		FVector End = Start + (GetActorForwardVector() * 100.0f);
		
		FHitResult HitResult(ForceInit);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		CollisionParams.AddIgnoredActor(PickedUpItem);
		CollisionParams.bTraceComplex = true;
		
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			 HitResult,
			 Start,
			 End,
			 ECC_Visibility, // Use a channel that makes sense for blocking geometry
			 CollisionParams
		 );

		if (!bHit) // Only drop if nothing was hit
		{
			FVector DropLocation = End;
			FTransform DropTransform(PickedUpItem->CustomRotation, DropLocation, PickedUpItem->GetActorScale());

			PickedUpItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			PickedUpItem->SetActorTransform(DropTransform);
			PickedUpItem->IsPickedUp = false;
			PickedUpItem = nullptr;
		}
	}
}
	
//Should Pick up item
void AMainCharacter::PickUpItemToHand()
{
	PickedUpItem = Cast<AQuestItemScript>(ClosestItem);
	if (!IsValid(PickedUpItem)) return;
	PickedUpItem->IsPickedUp = true;
	ClosestItem = nullptr;
	if (IsValid(ClosestSocket))
	{
		if (ClosestSocket->CurrentActorInSocket == PickedUpItem)
		{
			ClosestSocket->CurrentActorInSocket = nullptr;
			ClosestSocket->QuestItemStaticMeshComponent->SetVisibility(true, false);
		}
	}
	PickedUpItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_rSocket");
}
	
//Should Place down item into Socket
void AMainCharacter::InsertItemIntoSocket()
{
	ClosestSocket->AttachToActor(PickedUpItem);
	//ClosestSocket->UpdateQuest(); //This is not in c++ yet
	PickedUpItem = nullptr;
}

void AMainCharacter::GetClosestItem(AActor* InActor)
{
	if (IsValid(InActor))
	{
		if (InActor->IsHidden()) return;
		if (IsValid(ClosestItem))
		{
			float CheckDistance = GetDistanceTo(InActor);
			if (CheckDistance < ClosestDistance)
			{
				ClosestItem = InActor;
				ClosestDistance = CheckDistance;
			}	
		}
		else
		{
			ClosestItem = InActor;
			ClosestDistance = GetDistanceTo(InActor);
		}
	}
}

