// Fill out your copyright notice in the Description page of Project Settings.

#include "Utils/EventBus/Listener/EventListener/UEventListener.h"
#include "Utils/EventBus/Listener/Interface/EventBusInterface.h"

void UEventListener::Notify(TObjectPtr<UObject> EventData)
{
	OnEventReceived.Broadcast(EventData.Get());
}

void UEventListener::Init(TScriptInterface<IEventBusInterface> SomeEventBus, const UClass* EventType)
{
	RegisteredEventBus = SomeEventBus;
	RegisteredEventType = EventType;
}

void UEventListener::ActivateListener()
{
	RegisteredEventBus->Subscribe(RegisteredEventType, this);
}

void UEventListener::DeactivateListener()
{
	RegisteredEventBus->Unsubscribe(RegisteredEventType, this);
}
