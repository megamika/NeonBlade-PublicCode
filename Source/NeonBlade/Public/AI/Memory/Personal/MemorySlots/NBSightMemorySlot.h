// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Memory/Personal/MemorySlots/NBMemorySlot.h"

#include "NBSightMemorySlot.generated.h"

USTRUCT(BlueprintType)
struct FSeenCharacterData
{
	GENERATED_BODY()

	float CharacterSeenForTime;
	float CharacterPerceptionFill;
};

USTRUCT(BlueprintType)
struct FSeenCharacters 
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<ANBCharacter*> SeenCharacters;

	UPROPERTY(BlueprintReadOnly)
	TMap<ANBCharacter*, FSeenCharacterData> CharacterData;
};

UCLASS()
class NEONBLADE_API UNBSightMemorySlot : public UNBMemorySlot
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	TMap<TEnumAsByte<ETeamAttitude::Type>, FSeenCharacters> SeenActorsMap;

	UFUNCTION(BlueprintCallable)
	void UpdateSeenActors(TArray<AActor*> Actors);

	UFUNCTION(BlueprintCallable)
	void UpdateSeenActorsSeenTime(float DeltaTime);

	UFUNCTION(BlueprintPure)
	float GetTimeThisCharacterWasSeenFor(const ANBCharacter* TargetCharacter);

	UFUNCTION(BlueprintPure)
	bool CanSeeThisCharacterWithAttitude(const ANBCharacter* TargetCharacter, ETeamAttitude::Type Attitude);

	UFUNCTION(BlueprintCallable)
	void SetCharactersPerceptionFill(ANBCharacter* TargetCharacter, float Value);

	UFUNCTION(BlueprintPure )
	float GetCharactersPerceptionFill(const ANBCharacter* TargetCharacter);

	UFUNCTION(BlueprintPure)
	TArray<ANBCharacter*> GetAllCurrentlySeenCharacters();

protected:

	virtual void OnInitialized() override;
};
