// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EventListenerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEventListenerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GP4_LYMBO_API IEventListenerInterface
{
	GENERATED_BODY()

private:
	friend class UEventBusObject;
	friend class IEventBusInterface;

	virtual void Notify(TObjectPtr<UObject> EventData) = 0;
};
