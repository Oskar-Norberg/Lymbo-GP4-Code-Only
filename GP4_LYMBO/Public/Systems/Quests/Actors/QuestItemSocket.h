// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Subsystem/Player/QuestObjectSubSystem.h"
#include "QuestItemSocket.generated.h"

UCLASS()
class GP4_LYMBO_API AQuestItemSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestItemSocket();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent>  SocketSphereComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* QuestItemNeededShapeReference  = nullptr;;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* QuestItemStaticMeshComponent  = nullptr;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestSocketIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SocketIsFrozen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestItemType QuestItemType = EQuestItemType::Character;;

	UPROPERTY(BlueprintReadOnly)
	bool SomethingInSocket = false;

	UPROPERTY(BlueprintReadWrite)
	AActor* CurrentActorInSocket = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
	void AttachToActor(AActor* InActor);
};
