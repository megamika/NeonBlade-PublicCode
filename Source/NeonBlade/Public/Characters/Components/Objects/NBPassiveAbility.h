// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NBCharacter.h"
#include "NBPassiveAbility.generated.h"


class UNBAbilitiesComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API UNBPassiveAbility : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ANBCharacter> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBAbilitiesComponent> Component;

	virtual UWorld* GetWorld() const override final;

	void Initialize(ANBCharacter* AssignedCharacter, UNBAbilitiesComponent* AssignedAbilitiesComponent);

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;

	void Activate();

	virtual void OnActivate() {}

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveActivate();

	void Tick(float DeltaSeconds);

	virtual void OnTick() {}

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveTick();
};
