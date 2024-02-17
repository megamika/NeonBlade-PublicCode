// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBSharedMemorySlot.generated.h"


class UNBSharedMemorySubsystem;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API UNBSharedMemorySlot : public UObject
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override final;

	UPROPERTY(BlueprintReadOnly)
	UNBSharedMemorySubsystem* MemorySubsystem;

	void Initialize(UNBSharedMemorySubsystem* AssignedMemorySubsystem); 
};
