// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AI/SharedMemory/MemorySlots/NBSharedTeamList.h"
#include "AI/SharedMemory/MemorySlots/NBSharedSearch.h"

#include "NBSharedMemorySubsystem.generated.h"

class UNBSharedMemorySlot;
class UNBSharedSight;
class UNBSharedSearch;

UCLASS()
class NEONBLADE_API UNBSharedMemorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBSharedTeamList> SharedTeamMemorySlot;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBSharedSight> SharedTeamSight;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBSharedSearch> SharedSearch;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void PostInitialize() override;

	TSet<TObjectPtr<UNBSharedMemorySlot>> TeamSlotMap;

	UFUNCTION(BlueprintCallable)
	void AddMemorySlot(UNBSharedMemorySlot* NewSlot);

};
