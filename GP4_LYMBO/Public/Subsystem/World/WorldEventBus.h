// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Utils/Eventbus/EventBusObject.h"
#include "Utils/Eventbus/Listener/Interface/EventBusInterface.h"
#include "WorldEventBus.generated.h"

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UWorldEventBus : public UWorldSubsystem, public IEventBusInterface
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	virtual void Publish(UObject* EventData, const UClass* EventType) override;
	virtual void Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) override;
	virtual void Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) override;

private:
	UPROPERTY()
	TObjectPtr<UEventBusObject> EventBus;
};
