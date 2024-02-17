// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NBCharacter.h"
#include "AI/Controller/NBAIController.h"

#include "NBMemorySlot.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API UNBMemorySlot : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* Character;
	UPROPERTY(BlueprintReadOnly)
	ANBAIController* Controller;

	void Initialize(ANBCharacter* AssignedCharacter, ANBAIController* AssignedController);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitialized();

	virtual UWorld* GetWorld() const override final;
protected:

	virtual void OnInitialized();
};
