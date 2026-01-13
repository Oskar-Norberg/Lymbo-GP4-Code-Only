// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Player/QuestSubsystem.h"

#include "Subsystem/Instance/ProgressionSubsystem/ProgressionSubsystem.h"

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	QuestSystem = NewObject<UQuestSystem>(this, UQuestSystem::StaticClass());
	checkf(QuestSystem, TEXT("UQuestSubsystem::Initialize: Failed to create QuestSystem"));

	QuestSystem->GetOnQuestSystemChangedHandle().AddDynamic(this, &UQuestSubsystem::HandleOnQuestSystemChanged);
	QuestSystem->GetOnQuestSystemCompletedHandle().AddDynamic(this, &UQuestSubsystem::HandleOnQuestSystemCompleted);
	QuestSystem->GetOnQuestSystemUpdatedHandle().AddDynamic(this, &UQuestSubsystem::HandleOnQuestSystemUpdated);
}

void UQuestSubsystem::Deinitialize()
{
	Super::Deinitialize();

	QuestSystem = nullptr;
}

void UQuestSubsystem::SetQuest(const AController* QuestInstigator, const UQuestDataAsset* QuestData)
{
	QuestSystem->SetQuest(QuestInstigator, QuestData);

	// TODO: Ugliest block of code ever seen. 
	// Register progress
	const auto* World = GetWorld();
	checkf(World, TEXT("UQuestSubsystem::HandleOnQuestSystemCompleted: World is null"));
	const auto* GameInstance = World->GetGameInstance();
	checkf(GameInstance, TEXT("UQuestSubsystem::HandleOnQuestSystemCompleted: GameInstance is null"));
	auto* ProgressionSystem = GameInstance->GetSubsystem<UProgressionSubsystem>();
	checkf(ProgressionSystem, TEXT("UQuestSubsystem::HandleOnQuestSystemCompleted: ProgressionSystem is null"));
	
	ProgressionSystem->AddTag(QuestSystem->GetQuest()->GetQuestStartedTag());

}

TScriptInterface<IQuestInterface> UQuestSubsystem::GetQuest() const
{
	return QuestSystem->GetQuest();
}

FOnQuestSystemCompleted& UQuestSubsystem::GetOnQuestSystemCompletedHandle()
{
	return OnQuestSystemCompleted;
}

FOnQuestSystemUpdated& UQuestSubsystem::GetOnQuestSystemUpdatedHandle()
{
	return OnQuestSystemUpdated;
}

FOnQuestSystemChanged& UQuestSubsystem::GetOnQuestSystemChangedHandle()
{
	return OnQuestSystemChanged;
}

void UQuestSubsystem::HandleOnQuestSystemCompleted()
{
	OnQuestSystemCompleted.Broadcast();

	// Register progress
	const auto* World = GetWorld();
	checkf(World, TEXT("UQuestSubsystem::HandleOnQuestSystemCompleted: World is null"));
	const auto* GameInstance = World->GetGameInstance();
	checkf(GameInstance, TEXT("UQuestSubsystem::HandleOnQuestSystemCompleted: GameInstance is null"));
	auto* ProgressionSystem = GameInstance->GetSubsystem<UProgressionSubsystem>();
	checkf(ProgressionSystem, TEXT("UQuestSubsystem::HandleOnQuestSystemCompleted: ProgressionSystem is null"));
	ProgressionSystem->AddTag(QuestSystem->GetQuest()->GetQuestFinishedTag());
	
	QuestSystem->ClearQuest();
}

void UQuestSubsystem::HandleOnQuestSystemUpdated()
{
	OnQuestSystemUpdated.Broadcast();
}

void UQuestSubsystem::HandleOnQuestSystemChanged(TScriptInterface<IQuestInterface> NewQuest)
{
	OnQuestSystemChanged.Broadcast(NewQuest);
}
