#include "Utils/States/EntityStateBase.h"
#include "Utils/StateMachines/StateMachineBase.h"

void UEntityStateBase::InitState(UStateMachineBase* StateMachine, UObject* StateMachineOwner, bool* StateBoolToBeUpdated)
{
	m_StateMachine = StateMachine;
	m_StateMachineObjectOwner = StateMachineOwner;
	m_bStateBoolToBeUpdated = StateBoolToBeUpdated;
}

void UEntityStateBase::EnterState()
{
	*m_bStateBoolToBeUpdated = true;
}

void UEntityStateBase::UpdateState(float DeltaTime)
{
}

void UEntityStateBase::ExitState()
{
	*m_bStateBoolToBeUpdated = false;
}
