// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Memory/Personal/MemorySlots/NBMemorySlot.h"
#include "NBSearchMemorySlot.generated.h"

class ANBSearchPoint;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NEONBLADE_API UNBSearchMemorySlot : public UNBMemorySlot
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	bool AlreadyCheckedLastKnownTargetLocation;

	UPROPERTY(EditDefaultsOnly)
	int MaxSearchPointHistorySize;
	
	UFUNCTION(BlueprintCallable)
	void AddSearchPointToHistory(ANBSearchPoint* SearchPoint);
	
	UFUNCTION(BlueprintPure)
	bool HasThisSearchPointBeenVisited(ANBSearchPoint* SearchPoint) const;

private:

	UPROPERTY()
	TArray<TObjectPtr<ANBSearchPoint>> SearchPointHistory;

};
