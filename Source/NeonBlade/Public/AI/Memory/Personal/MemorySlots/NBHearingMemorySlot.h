// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Memory/Personal/MemorySlots/NBMemorySlot.h"
#include "NBAIFunctionLibrary.h"
#include "NBHearingMemorySlot.generated.h"




USTRUCT(BlueprintType)
struct FNoiseData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	AActor* Actor;
};

USTRUCT(BlueprintType)
struct FNoiseCollection
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, FNoiseData> NoiseDataMap;
};


UCLASS()
class NEONBLADE_API UNBHearingMemorySlot : public UNBMemorySlot
{
	GENERATED_BODY()

public:

	virtual void OnInitialized() override;

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<ENBNoiseType>, FNoiseCollection> NoiseTypesMap;

	UFUNCTION(BlueprintCallable)
	void UpdateHeardActors(TArray<AActor*> UpdatedActors);

	UFUNCTION(BlueprintPure)
	FNoiseData GetNoiseDataFromLocation(const FVector Location, const ENBNoiseType NoiseType, bool& OutSucess);

	UFUNCTION(BlueprintPure)
	TArray<FVector> GetAllNoiseLocationsForNoiseType(ENBNoiseType NoiseType);

};
