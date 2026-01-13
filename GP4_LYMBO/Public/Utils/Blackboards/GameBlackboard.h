#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameBlackboard.generated.h"

USTRUCT()
struct FGameBlackBoardEntry
{
	GENERATED_BODY()
	
	TVariant<int, float, FGameplayTag, bool> BlackboardValue;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_LYMBO_API UGameBlackboard : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TMap<FName, FGameBlackBoardEntry> BlackboardEntries;

public:
	template <typename T>
	void SetBlackBoardEntry(FName MapKey, T SomeValue)
	{
		FGameBlackBoardEntry NewEntry = FGameBlackBoardEntry();
		NewEntry.BlackboardValue.Set<T>(SomeValue);
		BlackboardEntries.Add(MapKey, NewEntry);
	}

	template <typename T>
	T GetBlackboardEntry(const FName& MapKey) const
	{
		checkf(BlackboardEntries.Contains(MapKey), TEXT("MAP KEY NOT FOUND"));
		return BlackboardEntries[MapKey].BlackboardValue.Get<T>();
	}

	template <typename T>
	bool HasBlackboardEntry(const FName& MapKey) const
	{
		if (BlackboardEntries.Contains(MapKey))
			return true;
		return false;
	}

	void RemoveBlackboardEntry(const FName& MapKey)
	{
		BlackboardEntries.Remove(MapKey);
	}
};
