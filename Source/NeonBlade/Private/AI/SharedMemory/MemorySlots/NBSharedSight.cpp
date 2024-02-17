// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SharedMemory/MemorySlots/NBSharedSight.h"

#include "Characters/NBCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

ANBCharacter* UNBSharedSight::PickTargetForCharacter(const ANBCharacter* Character)
{
	EnsureTeamExists(Character->CharacterTeam);

	ANBCharacter* Result = nullptr;
	
	TSet<ANBCharacter*> Targets;
	WatcherMap[Character->CharacterTeam].SharedLastKnownTargetLocations.GetKeys(Targets);

	float MinDistance = UE_BIG_NUMBER;
	for (ANBCharacter* Target : Targets)
	{
		const float CurrentDistance = Target->GetDistanceTo(Character);

		if (CurrentDistance < MinDistance)
		{
			MinDistance = CurrentDistance;
			Result = Target;
		}
	}

	return Result;
}

void UNBSharedSight::UpdateTargetSeenTime(const ECharacterTeam Team, ANBCharacter* Target)
{
	if (!Target) return;

	EnsureTeamExists(Team);

	WatcherMap[Team].TargetWasSeenTime.Add(Target, UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()));
}

float UNBSharedSight::GetTimeSinceTargetWasSeen(const ECharacterTeam Team, const ANBCharacter* Target)
{
	if (!Target) return UE_BIG_NUMBER;

	EnsureTeamExists(Team);

	if (!WatcherMap[Team].TargetWasSeenTime.Contains(Target))
	{
		return UE_BIG_NUMBER;
	}

	return UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()) - WatcherMap[Team].TargetWasSeenTime[Target];
}

void UNBSharedSight::AddCharacterCanSeeTarget(ANBCharacter* Character)
{
	EnsureTeamExists(Character->CharacterTeam);

	WatcherMap[Character->CharacterTeam].Characters.Add(Character);
}

void UNBSharedSight::RemoveCharacterCanSeeTarget(ANBCharacter* Character)
{
	EnsureTeamExists(Character->CharacterTeam);

	WatcherMap[Character->CharacterTeam].Characters.Remove(Character);
}

bool UNBSharedSight::CanAnyoneInTeamSeeTarget(const ECharacterTeam Team)
{
	EnsureTeamExists(Team);

	return !WatcherMap[Team].Characters.IsEmpty();
}

void UNBSharedSight::SetCharactersLastKnownPosition(const ECharacterTeam Team, ANBCharacter* Target, const FVector Location)
{
	if (!Target) return;

	EnsureTeamExists(Team);

	WatcherMap[Team].SharedLastKnownTargetLocations.Add(Target, Location);
}

void UNBSharedSight::SetCharactersApproximateLastKnownPosition(const ECharacterTeam Team, ANBCharacter* Target, const FVector Location)
{
	if (!Target) return;

	EnsureTeamExists(Team);

	const float TimeSinceLastSeen = GetTimeSinceTargetWasSeen(Team, Target);

	if (TimeSinceLastSeen < 0.1f)
	{
		return;
	}

	WatcherMap[Team].SharedLastKnownTargetLocations.Add(Target, Location);
}

FVector UNBSharedSight::GetCharactersLastKnownPosition(const ECharacterTeam Team, const ANBCharacter* Target, bool& OutSucess)
{
	EnsureTeamExists(Team);
	OutSucess = true;

	if (!WatcherMap[Team].SharedLastKnownTargetLocations.Contains(Target))
	{
		OutSucess = false;
		return FVector::Zero();
	}

	return WatcherMap[Team].SharedLastKnownTargetLocations[Target];
}

void UNBSharedSight::EnsureTeamExists(const ECharacterTeam Team)
{
	if (!WatcherMap.Contains(Team))
	{
		WatcherMap.Add(Team, FTargetWatchers());
	}
}