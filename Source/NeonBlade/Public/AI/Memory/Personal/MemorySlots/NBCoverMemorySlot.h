// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppUEBlueprintCallableFunctionUnused
#pragma once

#include "CoreMinimal.h"
#include "AI/Memory/Personal/MemorySlots/NBMemorySlot.h"
#include "NBCoverMemorySlot.generated.h"

class ANBCoverPoint;

/**
 * 
 */
UCLASS()
class NEONBLADE_API UNBCoverMemorySlot : public UNBMemorySlot
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	int MaxCoverHistorySize = 5;

	UPROPERTY(BlueprintReadOnly)
	TArray<ANBCoverPoint*> CoverHistory;
	
	UPROPERTY(BlueprintReadOnly)
	ANBCoverPoint* ReservedCover;

	UFUNCTION(BlueprintCallable)
	void ReserveCover(ANBCoverPoint* Cover);

	UFUNCTION(BlueprintCallable)
	void ReleaseCover();

	UFUNCTION(BlueprintCallable)
	void AddCoverPointToHistory(ANBCoverPoint* CoverPoint);

	UFUNCTION(BlueprintPure)
	bool HasRecentlyVisitedThisCoverPoint(ANBCoverPoint* CoverPoint) const;

};
