#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Utils/StateMachines/StateMachineBase.h"
#include "EntityStateBase.generated.h"

class UPlayerCharacter;

UCLASS()
class GP4_LYMBO_API UEntityStateBase : public UObject
{
	GENERATED_BODY()

public:
	UEntityStateBase(const FObjectInitializer& ObjectInitializer){}
	virtual void InitState(UStateMachineBase* StateMachine, UObject* StateMachineOwner, bool* StateMachineBoolToBeUpdated);
	virtual void EnterState();
	virtual void UpdateState(float DeltaTime);
	virtual void ExitState();

protected:
	UPROPERTY()
	TObjectPtr<UStateMachineBase> m_StateMachine;
	UPROPERTY()
	TObjectPtr<UObject> m_StateMachineObjectOwner;

	bool* m_bStateBoolToBeUpdated = nullptr;
};
