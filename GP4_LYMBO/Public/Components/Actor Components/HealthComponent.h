// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "HealthComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakenDamage);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecoveredHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_LYMBO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	FTimerHandle IFrameTimerHandle;
	
public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IFramesDuration = .2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanTakeDamage = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanRecoverHealth = true;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void EnableDamage();

public:

	UFUNCTION(BlueprintCallable)
	void Death();
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage, UDamageType* DamageType, AController* WhoDamagedMe, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void RecoverHealth(float Healing);
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnTakenDamage OnTakenDamage;
	UPROPERTY(BlueprintAssignable)
	FOnTakenDamage OnRecoveredHealth;
};
