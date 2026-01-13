// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Listener/Interface/EventBusInterface.h"
#include "UObject/Object.h"
#include "EventBusObject.generated.h"

USTRUCT()
struct FEventBusObjects
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TScriptInterface<IEventListenerInterface>> Listeners;
};

/**
 * 
 */
UCLASS()
class GP4_LYMBO_API UEventBusObject : public UObject, public IEventBusInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "EventBus")
	// TODO: Shouldn't pass in event type as parameter. Just call get type on EventObject
	virtual void Publish(UObject* EventData, const UClass* EventType) override;
	
	virtual void Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) override;
	virtual void Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback) override;

private:
	UPROPERTY()
	TMap<const UClass*, FEventBusObjects> EventListeners;
};
