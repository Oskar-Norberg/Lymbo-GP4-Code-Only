#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimatedMovableCharacter.generated.h"

UENUM(BlueprintType)
enum ECharacterMovementMode
{
	WALKING,
	RUNNING
};


UINTERFACE(Blueprintable)
class UAnimatedMovableCharacter : public UInterface
{
	GENERATED_BODY()
};

class IAnimatedMovableCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetMaxMovementSpeed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetCurrentMovementSpeed();
		
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetWalkSpeed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetRunSpeed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMovementSpeed(float SomeSpeed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SwitchMovementMode(ECharacterMovementMode SomeMovementMode);
	
	virtual void SwitchMovementMode_Implementation(ECharacterMovementMode SomeMovementMode);
};
