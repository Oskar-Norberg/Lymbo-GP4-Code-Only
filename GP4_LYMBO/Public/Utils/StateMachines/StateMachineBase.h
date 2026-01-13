#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateMachineBase.generated.h"

class UEntityStateBase;

UCLASS()
class GP4_LYMBO_API UStateMachineBase : public UObject
{
	GENERATED_BODY()

public:
	UStateMachineBase(const FObjectInitializer& ObjectInitializer){}
	virtual void InitStateMachine(AActor* Owner);
	virtual void AddStates();
	virtual void UpdateStateMachine(float DeltaTime);
	virtual void InitializeNewPlayerState(UClass* StateClass, bool* bPlayerStateMachineBoolToBeUpdated);
	virtual void SwitchState(UClass* NewStateClass);
	AActor* GetOwner();
	void ToggleTransitionLocked(bool bTransition);

protected:
	UPROPERTY()
	TObjectPtr<UEntityStateBase> m_CurrentState;
	UPROPERTY()
	TMap<UClass*, UEntityStateBase*> m_StateObjects;
	AActor* m_Owner = nullptr;

private:
	bool b_IsTransitioning = false;
	bool b_TransitionLocked = false;
};
