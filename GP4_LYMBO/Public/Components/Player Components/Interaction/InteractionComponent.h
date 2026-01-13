#pragma once

#include "CoreMinimal.h"
#include "Systems/Interactions/InteractionBase.h"
#include "Systems/Interactions/Interactor_Interface.h"
#include "Systems/Interactions/UniversalInteractionSubsystemData.h"
#include "UObject/Object.h"
#include "InteractionComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class GP4_LYMBO_API UInteractionComponent : public UActorComponent, public IInteractor_Interface
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	UFUNCTION(BlueprintCallable)
	virtual void BeginInteraction_Implementation() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void EndInteraction_Implementation() override;
	
protected:
	virtual void TickComponent(float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DoInteractionTrace();

	UFUNCTION(BlueprintCallable)
	void TryInteractingWithObject(AActor* ActorFound);
	
	UFUNCTION(BlueprintCallable)
	void StopInteractingWithObject();
	
	UFUNCTION(BlueprintCallable)
	bool IsInteractableInFrontOfOwner(AActor* Interactable);

protected:
	UPROPERTY(BlueprintReadWrite, Category="Interaction")
	UObject* CurrentInteractable = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Mediator")
	UInteractionBase* CurrentInteractionContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	float DotProductInteractionLimit = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	UUniversalInteractionSubsystemData* InteractionSubsystemData = nullptr;
};
