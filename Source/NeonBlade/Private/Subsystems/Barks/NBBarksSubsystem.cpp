// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Barks/NBBarksSubsystem.h"
#include "Characters/NBCharacter.h"

#include "Debug/NBDebugLibrary.h"
#include "Debug/NBDebugTags.h"
#include "AI/SharedMemory/NBSharedMemorySubsystem.h"
#include "AI/Controller/NBAIController.h"


bool UNBBarksSubsystem::CheckValidity(const ANBCharacter* Character)
{
	if (!Character) return false;

	const ECharacterTeam Team = Character->CharacterTeam;
	if (!UsedBarksMap.Contains(Team))
	{
		UsedBarksMap.Add(Team, FSaidBark());
	}

	return true;
}

void UNBBarksSubsystem::Tick(const float DeltaTime)
{
	for (const TPair<ECharacterTeam, FSaidBark>& pair : UsedBarksMap)
	{
		FSaidBark TeamBarkData = pair.Value;
		for (const TPair<FString, float>& subPair : TeamBarkData.UsedBarks)
		{
			FString Key = subPair.Key;
			UsedBarksMap[pair.Key].UsedBarks[Key] -= DeltaTime;

			UNBDebugLibrary::NBPrint(this, UNBDebugTags::DebugTag_Barks(), Key + FString::SanitizeFloat(TeamBarkData.UsedBarks[Key]), FName(Key));

			if (UsedBarksMap[pair.Key].UsedBarks[Key] <= 0.0f)
			{
				UsedBarksMap[pair.Key].UsedBarks.Remove(Key);
			}
		}
	}
}

ANBCharacter* UNBBarksSubsystem::GetClosestBarkResponder(const ANBCharacter* Barker) const
{
	if (!GetWorld()) return nullptr;
	const UNBSharedMemorySubsystem* SharedMemory = GetWorld()->GetSubsystem<UNBSharedMemorySubsystem>();
	if (!SharedMemory) return nullptr;

	float MinDistance = UE_BIG_NUMBER;
	TObjectPtr<ANBCharacter> ChosenCharacter;
	TArray<ANBAIController*> AllControllers = SharedMemory->SharedTeamMemorySlot->GetAllControllersInTeam(
		Barker->CharacterTeam);
	for (const auto Controller : AllControllers)
	{
		ANBCharacter* Character = Controller->GetPawn<ANBCharacter>();
		if (!Character) continue;
		if (Character == Barker) continue;

		const float Distance = Barker->GetDistanceTo(Character);
		if (Distance > 1250.0f) continue;

		if (Distance < MinDistance) 
		{
			MinDistance = Distance;
			ChosenCharacter = Character;
			
		}
	}

	return ChosenCharacter;
}

void UNBBarksSubsystem::ReserveBark(const ANBCharacter* Character, const FString& Bark, const float Time)
{
	if (!CheckValidity(Character)) return;

	const ECharacterTeam Team = Character->CharacterTeam;

	UsedBarksMap[Team].UsedBarks.Add(Bark, Time);
}

void UNBBarksSubsystem::FreeBark(const ANBCharacter* Character, const FString& Bark)
{
	if (!CheckValidity(Character)) return;

	const ECharacterTeam Team = Character->CharacterTeam;
	
	UsedBarksMap[Team].UsedBarks.Remove(Bark);
}

// ReSharper disable once CppPassValueParameterByConstReference
bool UNBBarksSubsystem::IsBarkReservedByAnyone(const ANBCharacter* Character, const FString Bark)
{
	if (!CheckValidity(Character)) return false;

	const ECharacterTeam Team = Character->CharacterTeam;
	
	return UsedBarksMap[Team].UsedBarks.Contains(Bark);
}


ETickableTickType UNBBarksSubsystem::GetTickableTickType() const
{
	return IsTemplate() ? ETickableTickType::Never : ETickableTickType::Always;
}


