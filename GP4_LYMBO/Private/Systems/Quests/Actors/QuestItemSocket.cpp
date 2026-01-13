// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Quests/Actors/QuestItemSocket.h"
#include "Systems/Quests/Actors/QuestItemScript.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "GameFramework/GameState.h"

#include "Kismet/GameplayStatics.h"
#include "Player/MainCharacter.h"

// Sets default values
AQuestItemSocket::AQuestItemSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SocketSceneComponent = CreateDefaultSubobject<USceneComponent>("SocketSceneComponent");
	SetRootComponent(SocketSceneComponent);

	SocketSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SocketRadiusSphereComponent"));
	SocketSphereComponent->InitSphereRadius(100);
	SocketSphereComponent->SetupAttachment(SocketSceneComponent);

	QuestItemStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("QuestItemStaticMeshComponent"));
	QuestItemStaticMeshComponent->SetupAttachment(SocketSceneComponent);
}

// Called when the game starts or when spawned
void AQuestItemSocket::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQuestItemSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentActorInSocket != nullptr) SomethingInSocket = true;
	else SomethingInSocket = false;

	if (SocketIsFrozen) QuestItemStaticMeshComponent->SetVisibility(false, false);
}

void AQuestItemSocket::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Something Touched The Socket"))
	//if (OtherActor == QuestItemNeeded)
	//{
	//	ACharacter* FindCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	//	AMainCharacter* ThePlayerBP = Cast<AMainCharacter>(FindCharacter);
	//	ThePlayerBP->PickedUpItem = nullptr;
	//	OtherActor->AttachToComponent(SocketSphereComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//	UE_LOG(LogTemp, Warning, TEXT("Quest Item Found Quest Socket"))
	//}
}

void AQuestItemSocket::AttachToActor(AActor* InActor)
{
	AQuestItemScript* CastQuestItemScript = Cast<AQuestItemScript>(InActor);
	if(CastQuestItemScript->QuestItemType == QuestItemType)
 	{
		ACharacter* FindCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
 		AMainCharacter* ThePlayerBP = Cast<AMainCharacter>(FindCharacter);
 		ThePlayerBP->PickedUpItem = nullptr;
 		CurrentActorInSocket = InActor;
		SomethingInSocket = true;
 		InActor->AttachToComponent(SocketSphereComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//InActor->SetActorRotation(SocketSphereComponent->GetRelativeRotation());
 		QuestItemStaticMeshComponent->SetVisibility(false, false);
 		UE_LOG(LogTemp, Warning, TEXT("Quest Item Found Quest Socket"))
 	}	
}
