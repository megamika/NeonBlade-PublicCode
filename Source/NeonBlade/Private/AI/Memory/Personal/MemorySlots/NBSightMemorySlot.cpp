// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Memory/Personal/MemorySlots/NBSightMemorySlot.h"

#include "NBAIFunctionLibrary.h"

void UNBSightMemorySlot::UpdateSeenActors(TArray<AActor*> Actors)
{
	for (const TPair<TEnumAsByte<ETeamAttitude::Type>, FSeenCharacters>& Pair : SeenActorsMap)
	{
		TSet<ANBCharacter*> DuplicatedSet;
		DuplicatedSet = SeenActorsMap[Pair.Key].SeenCharacters;
		for (ANBCharacter* SeenCharacter : DuplicatedSet)
		{
			if (!Actors.Contains(SeenCharacter))
			{
				SeenActorsMap[Pair.Key].SeenCharacters.Remove(SeenCharacter);
			}
		}
	}

	for (AActor* SeenActor : Actors) 
	{
		if (!SeenActor) continue;

		ANBCharacter* SeenCharacter = Cast<ANBCharacter>(SeenActor);

		if (!Character) continue;

		const ETeamAttitude::Type Attitude = UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(Character, SeenCharacter);


		if (!SeenActorsMap[Attitude].CharacterData.Contains(SeenCharacter))
		{
			SeenActorsMap[Attitude].CharacterData.Add(SeenCharacter, FSeenCharacterData());
		}

		if (!SeenActorsMap[Attitude].SeenCharacters.Contains(SeenCharacter))
		{
			SeenActorsMap[Attitude].SeenCharacters.Add(SeenCharacter);
			SeenActorsMap[Attitude].CharacterData[SeenCharacter].CharacterPerceptionFill = 0.0f;
			SeenActorsMap[Attitude].CharacterData[SeenCharacter].CharacterSeenForTime = 0.0f;
		}
	}

}

void UNBSightMemorySlot::UpdateSeenActorsSeenTime(const float DeltaTime)
{
	for (const TPair<TEnumAsByte<ETeamAttitude::Type>, FSeenCharacters>& pair : SeenActorsMap)
	{
		for (const ANBCharacter* SeenCharacter : pair.Value.SeenCharacters) 
		{
			SeenActorsMap[pair.Key].CharacterData[SeenCharacter].CharacterSeenForTime += DeltaTime;
		}
	}
}

float UNBSightMemorySlot::GetTimeThisCharacterWasSeenFor(const ANBCharacter* TargetCharacter)
{
	const ETeamAttitude::Type Attitude = UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(Character, TargetCharacter);

	if (SeenActorsMap[Attitude].SeenCharacters.Contains(TargetCharacter))
	{
		return SeenActorsMap[Attitude].CharacterData[TargetCharacter].CharacterSeenForTime;
	}
	
	return 0.0f;
}

bool UNBSightMemorySlot::CanSeeThisCharacterWithAttitude(const ANBCharacter* TargetCharacter, const ETeamAttitude::Type Attitude)
{
	return SeenActorsMap[Attitude].SeenCharacters.Contains(TargetCharacter);
}

void UNBSightMemorySlot::SetCharactersPerceptionFill(ANBCharacter* TargetCharacter, const float Value)
{
	if (!TargetCharacter)
	{
		return;
	}

	const ETeamAttitude::Type Attitude = UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(Character, TargetCharacter);
	if (!SeenActorsMap[Attitude].SeenCharacters.Contains(TargetCharacter))
	{
		return;
	}

	SeenActorsMap[Attitude].CharacterData[TargetCharacter].CharacterPerceptionFill = Value;
}

float UNBSightMemorySlot::GetCharactersPerceptionFill(const ANBCharacter* TargetCharacter)
{
	const ETeamAttitude::Type Attitude = UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(Character, TargetCharacter);
	if (!CanSeeThisCharacterWithAttitude(TargetCharacter, Attitude))
	{
		return 0.0f;
	}

	return SeenActorsMap[Attitude].CharacterData[TargetCharacter].CharacterPerceptionFill;
}

TArray<ANBCharacter*> UNBSightMemorySlot::GetAllCurrentlySeenCharacters()
{
	TArray<ANBCharacter*> Result;

	for (const TPair<TEnumAsByte<ETeamAttitude::Type>, FSeenCharacters>& pair : SeenActorsMap)
	{
		for (ANBCharacter* LoopedCharacter : SeenActorsMap[pair.Key].SeenCharacters) 
		{
			Result.Add(LoopedCharacter);
		}
	}

	return Result;
}

void UNBSightMemorySlot::OnInitialized()
{
	SeenActorsMap.Add(ETeamAttitude::Friendly, FSeenCharacters());
	SeenActorsMap.Add(ETeamAttitude::Neutral, FSeenCharacters());
	SeenActorsMap.Add(ETeamAttitude::Hostile, FSeenCharacters());
}
