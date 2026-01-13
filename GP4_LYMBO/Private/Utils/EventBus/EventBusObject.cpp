// Fill out your copyright notice in the Description page of Project Settings.

#include "Utils/EventBus/EventBusObject.h"
#include "Utils/EventBus/Listener/Interface/EventListenerInterface.h"

void UEventBusObject::Publish(UObject* EventData, const UClass* EventType)
{
	const auto* ListenerSet = EventListeners.Find(EventType);
	
	if (ListenerSet)
	{
		// Take Snapshot of all listeners
		auto CopyListeners = ListenerSet->Listeners;
		
		for (const TScriptInterface<IEventListenerInterface>& Listener : CopyListeners)
		{
			if (Listener && Listener.GetInterface() && IsValid(Listener.GetObject()))
			{
				Listener.GetInterface()->Notify(EventData);
			}
		}	
	}
}

void UEventBusObject::Subscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	auto& ListenerSet = EventListeners.FindOrAdd(EventType);
	ListenerSet.Listeners.Add(SomeCallback);
}

void UEventBusObject::Unsubscribe(const UClass* EventType, TScriptInterface<IEventListenerInterface> SomeCallback)
{
	auto* ListenerSet = EventListeners.Find(EventType);
	
	if (ListenerSet)
	{
		ListenerSet->Listeners.Remove(SomeCallback);
	}
}
