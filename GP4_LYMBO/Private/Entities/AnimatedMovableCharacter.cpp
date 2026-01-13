#include "Entities/AnimatedMovableCharacter.h"

void IAnimatedMovableCharacter::SwitchMovementMode_Implementation(ECharacterMovementMode SomeMovementMode)
{
	UObject* InterfaceImplementer = Cast<UObject>(this);

	if (!InterfaceImplementer)
	{
		return;
	}
		
	switch (SomeMovementMode)
	{
	default:
	case ECharacterMovementMode::WALKING:
		Execute_SetCurrentMovementSpeed(InterfaceImplementer, Execute_GetWalkSpeed(InterfaceImplementer));
		break;

	case ECharacterMovementMode::RUNNING:
		Execute_SetCurrentMovementSpeed(InterfaceImplementer, Execute_GetRunSpeed(InterfaceImplementer));
		break;
	}
}