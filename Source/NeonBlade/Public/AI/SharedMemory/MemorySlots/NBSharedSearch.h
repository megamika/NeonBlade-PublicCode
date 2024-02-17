// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SharedMemory/MemorySlots/NBSharedMemorySlot.h"
#include "NBSharedSearch.generated.h"

class ANBSearchPoint;
class ANBCharacter;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API UNBSharedSearch : public UNBSharedMemorySlot
{
	GENERATED_BODY()

public:
	
	void RegisterSearchPoint(ANBSearchPoint* SearchPoint);

	UFUNCTION(BlueprintPure)
	ANBSearchPoint* GetBestSearchPoint(const ANBCharacter* Character, const FVector Location, float CutoffDistance = 5000.0f);

private:

	TSet<ANBSearchPoint*> SearchPoints;

};
