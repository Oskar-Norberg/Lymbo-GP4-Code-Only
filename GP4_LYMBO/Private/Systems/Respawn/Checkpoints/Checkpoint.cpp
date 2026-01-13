// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Respawn/Checkpoints/Checkpoint.h"

#include "Components/ArrowComponent.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RespawnPoint"));
	//RootComponent = PointComponent;

	PointComponent->SetMobility(EComponentMobility::Movable);
	PointComponent->SetupAttachment(RootComponent);
	
#if WITH_EDITORONLY_DATA

	RespawnPointIcon = CreateDefaultSubobject<UBillboardComponent>(TEXT("RespawnPointIcon"));
	RespawnPointIcon->SetupAttachment(PointComponent);

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("/Engine/EditorResources/S_Terrain_256"));
	if (IconTexture.Succeeded())
	{
		RespawnPointIcon->SetSprite(IconTexture.Object);
	}

	RespawnPointIcon->bIsScreenSizeScaled = true;
	RespawnPointIcon->SetHiddenInGame(true);
	
#endif
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ACheckpoint::GetRespawnLocation()
{
	RespawnLocation = PointComponent->GetComponentLocation();
	return RespawnLocation;
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

