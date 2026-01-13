// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/World/WorldEventBus.h"

void UWorldEventBus::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	EventBus = NewObject<UEventBusObject>(this);
}

void UWorldEventBus::Publish(UObject* EventData, const UClass* EventType)
{
	EventBus->Publish(EventData, EventType);
}

void UWorldEventBus::Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	EventBus->Subscribe(EventType, SomeCallback);
}

void UWorldEventBus::Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	EventBus->Unsubscribe(EventType, SomeCallback);
}
