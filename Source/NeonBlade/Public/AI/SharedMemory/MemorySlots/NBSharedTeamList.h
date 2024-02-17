// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SharedMemory/MemorySlots/NBSharedMemorySlot.h"
#include "Characters/NBCharacter.h"

#include "NBSharedTeamList.generated.h"

class ANBAIController;

struct FTeamSet
{
	TArray<ANBAIController*> Value;
};

UCLASS()
class NEONBLADE_API UNBSharedTeamList : public UNBSharedMemorySlot
{
	GENERATED_BODY()

	TArray<TObjectPtr<ANBAIController>> Controllers;
	TMap<ECharacterTeam, FTeamSet> TeamControllerMap;

public:

	void RegisterController(ANBAIController* Controller);

	void DeReregisterController(ANBAIController* Controller);

	UFUNCTION(BlueprintPure)
	TArray<ANBAIController*> GetAllControllers();

	UFUNCTION(BlueprintPure)
	TArray<ANBAIController*> GetAllControllersInTeam(ECharacterTeam Team);

};
