// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/EventBus/Listener/Interface/EventListenerInterface.h"
#include "UObject/Object.h"
#include "UEventListener.generated.h"

class IEventBusInterface;
class UEventBusObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDelegate, UObject*, EventData);

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GP4_LYMBO_API UEventListener : public UActorComponent, public IEventListenerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FEventDelegate OnEventReceived;

public:
	// TODO: EventType can probably be a UPROPERTY. EventBus can then be passed in through the ActivateListener. Removing the need for an Init funciton.
	UFUNCTION(BlueprintCallable, Category = "EventBus|Listener")
	void Init(TScriptInterface<IEventBusInterface> SomeEventBus, const UClass* EventType);
	UFUNCTION(BlueprintCallable, Category = "EventBus|Listener")
	void ActivateListener();
	UFUNCTION(BlueprintCallable, Category = "EventBus|Listener")
	void DeactivateListener();

private:
	UPROPERTY(EditDefaultsOnly)
	const UClass* RegisteredEventType;
	UPROPERTY()
	TScriptInterface<IEventBusInterface> RegisteredEventBus;

	virtual void Notify(TObjectPtr<UObject> EventData) override;
};
