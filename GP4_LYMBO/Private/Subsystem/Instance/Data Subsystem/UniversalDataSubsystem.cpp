#include "Subsystem/Instance/Data Subsystem/UniversalDataSubsystem.h"

#include "Core/Instance/LymboGameInstance.h"

const UUniversalItemData* UUniversalDataSubsystem::GetUniversalItemData()
{
	if (SubsystemDataMap.Contains(UUniversalItemData::StaticClass()))
	{
		return Cast<UUniversalItemData>(SubsystemDataMap[UUniversalItemData::StaticClass()]);
	}
	
	return Cast<UUniversalItemData>(GetInstanceData(UUniversalItemData::StaticClass()));
}

const URetroGraphicsSettingsDataAsset* UUniversalDataSubsystem::GetRetroGraphicsSettings()
{
	if (SubsystemDataMap.Contains(URetroGraphicsSettingsDataAsset::StaticClass()))
	{
		return Cast<URetroGraphicsSettingsDataAsset>
		(SubsystemDataMap[URetroGraphicsSettingsDataAsset::StaticClass()]);
	}

	return Cast<URetroGraphicsSettingsDataAsset>(GetInstanceData(URetroGraphicsSettingsDataAsset::StaticClass()));
}

void UUniversalDataSubsystem::InitializeUniversalItemData()
{
	for (auto& itemData : UniversalItemData->ItemDataMap)
	{
		itemData.Value.ItemDisplayName = itemData.Key.GetTagLeafName();
	}
}

UObject* UUniversalDataSubsystem::GetInstanceData(UClass* DataClass)
{
	if (DataClass == nullptr)
		return nullptr;

	ULymboGameInstance* GameInstance = Cast<ULymboGameInstance>(GetWorld()->GetGameInstance());
	checkf(GameInstance != nullptr, TEXT("INVALID GAME INSTANCE"));

	UObject* SubsystemDataObject = *GameInstance->SubsystemDataArray.FindByPredicate(
		[=](const UObject* DataObject)
		{
			return DataObject->GetClass() == DataClass;
		}
		);

	if (SubsystemDataObject != nullptr)
	{
		SubsystemDataMap.Add(DataClass, SubsystemDataObject);
		GameInstance->SubsystemDataArray.Remove(SubsystemDataObject);
	}
	return SubsystemDataObject;
}
