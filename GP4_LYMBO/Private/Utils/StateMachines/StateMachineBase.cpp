#include "Utils/StateMachines/StateMachineBase.h"
#include "Utils/States/EntityStateBase.h"

void UStateMachineBase::InitStateMachine(AActor* Owner)
{
	m_Owner = Owner;
}

void UStateMachineBase::AddStates()
{
}

void UStateMachineBase::InitializeNewPlayerState(UClass* StateClass, bool* bPlayerStateMachineBoolToBeUpdated)
{
	UEntityStateBase* NewState = NewObject<UEntityStateBase>(this, StateClass);
	NewState->InitState(this, GetOwner(), bPlayerStateMachineBoolToBeUpdated);
	m_StateObjects.Add(StateClass, NewState);
}

void UStateMachineBase::UpdateStateMachine(float DeltaTime)
{
	m_CurrentState->UpdateState(DeltaTime);
}

void UStateMachineBase::SwitchState(UClass* NewStateClass)
{
	if (m_CurrentState.GetClass() == NewStateClass || m_CurrentState == nullptr || b_IsTransitioning || b_TransitionLocked)
		return;

	b_IsTransitioning = true;
	m_CurrentState->ExitState();
	m_CurrentState = m_StateObjects[NewStateClass];
	m_CurrentState->EnterState();
	b_IsTransitioning = false;
}

AActor* UStateMachineBase::GetOwner()
{
	return m_Owner;
}

void UStateMachineBase::ToggleTransitionLocked(bool bTransition)
{
	b_TransitionLocked = bTransition;
}
