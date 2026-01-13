#include "Subsystem/Instance/Interaction Subsystem/UniversalInteractionSubsystem.h"

#include "Core/Instance/LymboGameInstance.h"
#include "Subsystem/Instance/Data Subsystem/UniversalDataSubsystem.h"
#include "Systems/Interactions/InteractionBase.h"

UInteractionBase* UUniversalInteractionSubsystem::GetInteraction(FGameplayTag InteractionTag)
{
	if (InteractionMap.Num() < 1)
	{
		InitializeMap();
	}
	checkf(InteractionMap.Contains(InteractionTag),
		TEXT("YOU HAVE NOT ADDED AN INTERACTION LOGIC BP TO THE DATA ASSET!!!"));
	
	return InteractionMap[InteractionTag];
}

void UUniversalInteractionSubsystem::InitializeMap()
{
	ULymboGameInstance* LymboGameInstance = Cast<ULymboGameInstance>(GetWorld()->GetGameInstance());
		
	UniversalInteractionSubsystemData =
		Cast<UUniversalInteractionSubsystemData>(GetGameInstance()->GetSubsystem<UUniversalDataSubsystem>()
			->GetInstanceData(UUniversalInteractionSubsystemData::StaticClass()));

	checkf(UniversalInteractionSubsystemData != nullptr, TEXT("INTERACTION SUBSYSTEM DATA ASSET DOES NOT EXIST!!"))
	
	for (FInteractionData interactionData : UniversalInteractionSubsystemData->InteractionDataArray)
	{
		if (interactionData.InteractionLogicSubclass != nullptr)
		{
			InteractionMap.Add(interactionData.InteractionTag,
			NewObject<UInteractionBase>(this, interactionData.InteractionLogicSubclass));
		}
	}
}

UInteractionBase* UUniversalInteractionSubsystem::GetDefaultInteraction()
{
	if (DefaultInteractionInstance == nullptr)
	{
		DefaultInteractionInstance = NewObject<UInteractionBase>(this, UInteractionBase::StaticClass());
	}
	return DefaultInteractionInstance;
}
