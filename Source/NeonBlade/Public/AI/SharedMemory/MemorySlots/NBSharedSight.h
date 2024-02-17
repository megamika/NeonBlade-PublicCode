// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SharedMemory/MemorySlots/NBSharedMemorySlot.h"
#include "NBSharedSight.generated.h"

enum class ECharacterTeam : uint8;
class ANBCharacter;


USTRUCT(BlueprintType)
struct FTargetWatchers
{
	GENERATED_BODY()

	TSet<ANBCharacter*> Characters;

	TMap<ANBCharacter*, FVector> SharedLastKnownTargetLocations;
	TMap<ANBCharacter*, float> TargetWasSeenTime;
};

UCLASS()
class NEONBLADE_API UNBSharedSight : public UNBSharedMemorySlot
{
	GENERATED_BODY()
	
	TMap<ECharacterTeam, FTargetWatchers> WatcherMap;
	

	UFUNCTION(BlueprintPure)
	ANBCharacter* PickTargetForCharacter(const ANBCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void UpdateTargetSeenTime(ECharacterTeam Team, ANBCharacter* Target);
	
	UFUNCTION(BlueprintPure)
	float GetTimeSinceTargetWasSeen(ECharacterTeam Team, const ANBCharacter* Target);

	UFUNCTION(BlueprintCallable)
	void AddCharacterCanSeeTarget(ANBCharacter* Character);
	
	UFUNCTION(BlueprintCallable)
	void RemoveCharacterCanSeeTarget(ANBCharacter* Character);

	UFUNCTION(BlueprintPure)
	bool CanAnyoneInTeamSeeTarget(ECharacterTeam Team);

	UFUNCTION(BlueprintCallable)
	void SetCharactersLastKnownPosition(ECharacterTeam Team, ANBCharacter* Target, FVector Location);

	UFUNCTION(BlueprintCallable)
	void SetCharactersApproximateLastKnownPosition(ECharacterTeam Team, ANBCharacter* Target, FVector Location);

	UFUNCTION(BlueprintPure)
	FVector GetCharactersLastKnownPosition(ECharacterTeam Team, const ANBCharacter* Target, bool& OutSucess);

	void EnsureTeamExists(ECharacterTeam Team);
};
