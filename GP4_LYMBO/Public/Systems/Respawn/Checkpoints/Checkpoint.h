// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Checkpoint.generated.h"

UCLASS()
class GP4_LYMBO_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpoint();
	
protected:

	UPROPERTY(EditAnywhere)
	FVector RespawnLocation = FVector::ZeroVector;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	FVector GetRespawnLocation();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoints")
	USceneComponent* PointComponent;

	#if WITH_EDITORONLY_DATA
	
	UPROPERTY(VisibleAnywhere, Category = "Checkpoints")
	UBillboardComponent* RespawnPointIcon;
	
	#endif
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
