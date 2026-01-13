#pragma once

#include "CoreMinimal.h"
#include "Data/RetroGraphicsSettingsDataAsset.h"
#include "Data/SpeakersDataAsset.h"
#include "Engine/GameInstance.h"
#include "Subsystem/Instance/Data Subsystem/UniversalItemData.h"
#include "Systems/Interactions/UniversalInteractionSubsystemData.h"
#include "LymboGameInstance.generated.h"


UCLASS(Abstract)
class GP4_LYMBO_API ULymboGameInstance : public UGameInstance
{
	GENERATED_BODY()

	friend class UUniversalDataSubsystem;
	friend class UUniversalInteractionSubsystem;
	friend class USpeakerDataSubsystem;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UObject*> SubsystemDataArray;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	TObjectPtr<USpeakersDataAsset> SpeakersDataAsset = nullptr;
};



