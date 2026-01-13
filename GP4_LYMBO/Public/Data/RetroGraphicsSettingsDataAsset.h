
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "RetroGraphicsSettingsDataAsset.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class UGraphicsPreset : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogStartDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogFadeLength = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogHeightOffset = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogHeightFadeLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawing")
	float PolygonDrawDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawing")
	float VertexSnapToggle = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawing")
	float GridSizeX = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawing")
	float GridSizeY = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drawing")
	float DrawDistanceGridSize = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor FogRGBA = FColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor GlobalLightColor = FColor::White;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API URetroGraphicsSettingsDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGraphicsPreset>> GraphicsPresetSubClasses;

	UPROPERTY(BlueprintReadOnly)
	TArray<UGraphicsPreset*> GraphicsPresetsList;

public:
	UFUNCTION(BlueprintCallable)
	UGraphicsPreset* GetGraphicsPreset(UClass* SomeGraphicsPresetClass)
	{
		if (GraphicsPresetsList.Num() == 0)
		{
			for (uint8 i = 0; i < GraphicsPresetSubClasses.Num(); i++)
			{
				GraphicsPresetsList.Add(NewObject<UGraphicsPreset>(this, GraphicsPresetSubClasses[i]));
			}
		}

		for (uint8 i = 0; i < GraphicsPresetsList.Num(); i++)
		{
			if (GraphicsPresetsList[i]->GetClass() == SomeGraphicsPresetClass)
			{
				return GraphicsPresetsList[i];
			}
		}
		return nullptr;
	}
};
