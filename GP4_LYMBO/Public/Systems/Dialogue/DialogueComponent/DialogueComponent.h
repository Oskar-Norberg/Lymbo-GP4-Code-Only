// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Systems/Dialogue/DataAsset/DialogueDataAsset.h"
#include "DialogueComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_LYMBO_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue")
	TObjectPtr<UDialogueDataAsset> DialogueDataAsset;
};
