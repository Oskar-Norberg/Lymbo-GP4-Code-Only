#pragma once

#include "CoreMinimal.h"
#include "UniversalItemData.h"
#include "Data/RetroGraphicsSettingsDataAsset.h"
#include "Subsystems/WorldSubsystem.h"
#include "UniversalDataSubsystem.generated.h"

UCLASS()
class GP4_LYMBO_API UUniversalDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UUniversalItemData* UniversalItemData = nullptr;

	UPROPERTY()
	URetroGraphicsSettingsDataAsset* RetroGraphicsSettings = nullptr;

	UPROPERTY()
	TMap<UClass*, UObject*> SubsystemDataMap;

	void InitializeUniversalItemData();

public:
	UFUNCTION(BlueprintCallable)
	const UUniversalItemData* GetUniversalItemData();

	UFUNCTION(BlueprintCallable)
	const URetroGraphicsSettingsDataAsset* GetRetroGraphicsSettings();

	UFUNCTION(BlueprintCallable)
	UObject* GetInstanceData(UClass* DataClass);
};


