// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NBCharacter.h"
#include "NBAbility.generated.h"

class UNBAbilitiesComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityActivation);

UCLASS(BlueprintType, Blueprintable)
class NEONBLADE_API UNBAbility : public UObject
{
	GENERATED_BODY()

	bool IsActive;

	TArray<UNBAbility*> BlockedByAbilities;
	TArray<UNBAbility*> BlocksAbilities;

	TArray<UNBAbility*> RequiredActiveAbilities;
	TArray<UNBAbility*> RequiredByAbilities;

public:

	void Initialize(ANBCharacter* AssignedCharacter, UNBAbilitiesComponent* AssignedComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnValuesSet();

	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* Character;

	UPROPERTY(BlueprintReadOnly)
	UNBAbilitiesComponent* Component;

	UFUNCTION(BlueprintPure)
	bool GetIsActive() const { return IsActive; }
	
	bool CheckIfBlockedByOtherAbilities();

	bool CheckIfRquiredAbilitiesAreActive();

	UFUNCTION(BlueprintCallable)
	bool TryActivate();

	UFUNCTION(BlueprintCallable)
	void Cancel();

    virtual void Activation();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveActivation();

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;

	virtual void Tick() {}

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveTick();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "CanActivate", meta = (ScriptName = "CanActivate"))
	bool K2_CanActivate();

	UFUNCTION(BlueprintCallable)
	void AddBlockedByAbility(UNBAbility* Ability);

	UFUNCTION(BlueprintCallable)
	void AddRequiredActiveAbility(UNBAbility* Ability);

	virtual void Cancellation();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveCancellation();

	virtual UWorld* GetWorld() const override final;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivation OnAbilityActivated;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivation OnAbilityCanceled;
};
