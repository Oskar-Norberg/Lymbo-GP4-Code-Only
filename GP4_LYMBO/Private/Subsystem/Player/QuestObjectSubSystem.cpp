// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Player/QuestObjectSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Systems/Quests/Actors/QuestItemScript.h"
#include "Systems/Quests/Actors/QuestItemSocket.h"

bool UQuestObjectSubsystem::AreQuestSocketsInUse(const TArray<int32>& Ints)
{
    bool Result = true;
    UWorld* World = GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("UQuestObjectSubsystem::AreQuestSocketsInUse - World is a nullptr"));
        return false;
    }
    TArray<AActor*> QuestSocketsInInstance;
    UGameplayStatics::GetAllActorsOfClass(World, AQuestItemSocket::StaticClass(), QuestSocketsInInstance);
    for (int32 Num : Ints)
    {
        for (AActor* Actor : QuestSocketsInInstance)
        {
            AQuestItemSocket* CheckingSocket = Cast< AQuestItemSocket>(Actor);
            if (CheckingSocket->QuestSocketIndex == Num && !CheckingSocket->SomethingInSocket)
            {
                Result = false;
            }
        }
    }

    if (Result) CurrentQuestPart++;
    return Result;
}

void UQuestObjectSubsystem::FreezeTheseQuestSockets(const TArray<int32>& Ints)
{
    UWorld* World = GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("UQuestObjectSubsystem::AreQuestSocketsInUse - World is a nullptr"));
        return;
    }
    TArray<AActor*> QuestSocketsInInstance;
    UGameplayStatics::GetAllActorsOfClass(World, AQuestItemSocket::StaticClass(), QuestSocketsInInstance);
    for (int32 Num : Ints)
    {
        for (AActor* Actor : QuestSocketsInInstance)
        {
            AQuestItemSocket* CheckingSocket = Cast< AQuestItemSocket>(Actor);
            if (CheckingSocket->QuestSocketIndex == Num)
            {
                CheckingSocket->SocketIsFrozen = true;
            }
        }
    }
}

void UQuestObjectSubsystem::UnFreezeTheseQuestSockets(const TArray<int32>& Ints)
{
    UWorld* World = GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("UQuestObjectSubsystem::AreQuestSocketsInUse - World is a nullptr"));
        return;
    }
    TArray<AActor*> QuestSocketsInInstance;
    UGameplayStatics::GetAllActorsOfClass(World, AQuestItemSocket::StaticClass(), QuestSocketsInInstance);
    for (int32 Num : Ints)
    {
        for (AActor* Actor : QuestSocketsInInstance)
        {
            AQuestItemSocket* CheckingSocket = Cast< AQuestItemSocket>(Actor);
            if (CheckingSocket->QuestSocketIndex == Num)
            {
                CheckingSocket->SocketIsFrozen = false;
            }
        }
    }
}

TArray<AActor*> UQuestObjectSubsystem::GetQuestSocketsActor(const TArray<int32>& QuestSocketIndexes)
{
    TArray<AActor*> ActorsInSelectedSockets;
    UWorld* World = GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("UQuestObjectSubsystem::AreQuestSocketsInUse - World is a nullptr"));
        return  ActorsInSelectedSockets;;
    }
    TArray<AActor*> QuestSocketsInInstance;
    UGameplayStatics::GetAllActorsOfClass(World, AQuestItemSocket::StaticClass(), QuestSocketsInInstance);
    for (int32 Num : QuestSocketIndexes)
    {
        for (AActor* Actor : QuestSocketsInInstance)
        {
            AQuestItemSocket* CheckingSocket = Cast< AQuestItemSocket>(Actor);
            if (CheckingSocket->QuestSocketIndex == Num)
            {
                AActor* ActorInSocket = Cast< AActor>(CheckingSocket->CurrentActorInSocket);
                if (IsValid(ActorInSocket)) ActorsInSelectedSockets.Add(ActorInSocket);
            }
        }
    }
    return ActorsInSelectedSockets;
}

AActor* UQuestObjectSubsystem::GetQuestSocketActor(const int32& QuestSocketIndex)
{
    UWorld* World = GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("UQuestObjectSubsystem::AreQuestSocketsInUse - World is a nullptr"));
        return nullptr;
    }
    TArray<AActor*> QuestSocketsInInstance;
    UGameplayStatics::GetAllActorsOfClass(World, AQuestItemSocket::StaticClass(), QuestSocketsInInstance);
    for (AActor* Actor : QuestSocketsInInstance)
        {
            AQuestItemSocket* CheckingSocket = Cast< AQuestItemSocket>(Actor);
            if (CheckingSocket->QuestSocketIndex == QuestSocketIndex)
            {
                AActor* ActorInSocket = Cast< AActor>(CheckingSocket->CurrentActorInSocket);
                if (IsValid(ActorInSocket)) return ActorInSocket;
            }
    }

    return nullptr;
}

bool UQuestObjectSubsystem::GetIfSocketsHaveCorrectActor(TArray<FString> WhichNames, const TArray<int32>& QuestSocketIndexes)
{
    int AllIsValid = 0;
    UWorld* World = GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogTemp, Error, TEXT("UQuestObjectSubsystem::AreQuestSocketsInUse - World is a nullptr"));
        return  false;;
    }
    TArray<AActor*> QuestSocketsInInstance;
    UGameplayStatics::GetAllActorsOfClass(World, AQuestItemSocket::StaticClass(), QuestSocketsInInstance);
    for (int32 Num : QuestSocketIndexes)
    {
        for (AActor* Actor : QuestSocketsInInstance)
        {
            AQuestItemSocket* CheckingSocket = Cast< AQuestItemSocket>(Actor);
            AQuestItemScript* CurrentActorInSocket = Cast<AQuestItemScript>(CheckingSocket->CurrentActorInSocket);
            if (!IsValid(CurrentActorInSocket)) continue;
                if (CheckingSocket->QuestSocketIndex == Num)
                {
                    for (FString Name : WhichNames)
                    {
                        if (CurrentActorInSocket->QuestItemName == Name)
                        {
                            AllIsValid++;
                        }   
                }
            }
        }
    }
    if (AllIsValid == QuestSocketIndexes.Num()) return true;
    else return false;
}