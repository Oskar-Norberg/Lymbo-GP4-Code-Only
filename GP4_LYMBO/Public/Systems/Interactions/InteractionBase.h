#pragma once

#include "CoreMinimal.h"
#include "Interaction_Interface.h"
#include "Core/Instance/LymboGameInstance.h"
#include "UObject/Object.h"
#include "InteractionBase.generated.h"

class UInteractionComponent;

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API UInteractionBase : public UObject, public IInteraction_Interface
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();
	virtual bool TryInteraction_Implementation(AController* SomeSourceController,
		const TScriptInterface<IInteractor_Interface>& SomeSourceInteractor,
		const TScriptInterface<IInteractable_Interface>& SomeTargetController) override;
	virtual void BeginInteraction_Implementation() override;
	virtual void EndInteraction_Implementation() override;

	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable)
	UGameInstance* GetGameInstance() const;

	UFUNCTION(BlueprintCallable)
	AActor* GetActorOfClass(UClass* SomeActorClass);
	
	UFUNCTION(BlueprintCallable)
	AController* GetCurrentSourceController();

	UFUNCTION(BlueprintCallable)
	TScriptInterface<IInteractor_Interface> GetCurrentInteractor();

	UFUNCTION(BlueprintCallable)
	TScriptInterface<IInteractable_Interface> GetCurrentInteractable();

protected:
	UPROPERTY(BlueprintReadOnly, Category="Interaction")
	TScriptInterface<IInteractable_Interface> CurrentInteractableTarget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Interaction")
	TScriptInterface<IInteractor_Interface> CurrentSourceInteractor = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	AController* CurrentSourceController = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Interaction")
	TObjectPtr<ULymboGameInstance> InteractionSubsystem = nullptr;
};
