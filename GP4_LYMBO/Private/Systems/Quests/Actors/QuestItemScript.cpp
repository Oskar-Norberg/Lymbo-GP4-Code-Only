// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Quests/Actors/QuestItemScript.h"

// Sets default values
AQuestItemScript::AQuestItemScript()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestItemScript::BeginPlay()
{
	Super::BeginPlay();
	InitTransform = GetActorTransform();
	if (CustomRotation == FRotator(0,0,0))
	{
		CustomRotation = GetActorRotation();
	}
}

// Called every frame
void AQuestItemScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	if (MaximumDistanceUntilRespawn == 0.0f) return;
	// if (CurrentLocation.X < InitTransform.GetLocation().X + MaximumDistanceUntilRespawn || CurrentLocation.Y < InitTransform.GetLocation().Y + MaximumDistanceUntilRespawn || CurrentLocation.Z <InitTransform.GetLocation().Z + MaximumDistanceUntilRespawn)
	// {
	// 	IsPickedUp = true;
	// 	SetActorTransform(FTransform(InitTransform));
	// }
	// else	if (CurrentLocation.X < ( InitTransform.GetLocation().X + MaximumDistanceUntilRespawn * -1)|| CurrentLocation.Y <  ( InitTransform.GetLocation().Y + MaximumDistanceUntilRespawn * -1) || CurrentLocation.Z <  ( InitTransform.GetLocation().Z + MaximumDistanceUntilRespawn * -1))
	// {
	// 	IsPickedUp = true;
	// 	SetActorTransform(InitTransform);
	// }

}

