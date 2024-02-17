// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SharedMemory/MemorySlots/NBSharedTeamList.h"

#include "AI/Controller/NBAIController.h"

void UNBSharedTeamList::RegisterController(ANBAIController* Controller)
{
	const ANBCharacter* Pawn = Controller->GetPawn<ANBCharacter>();
	if (!Pawn)
	{
		return;
	}


	Controllers.Add(Controller);

	if (!TeamControllerMap.Contains(Pawn->CharacterTeam))
	{
		TeamControllerMap.Add(Pawn->CharacterTeam, FTeamSet());
	}
	TeamControllerMap[Pawn->CharacterTeam].Value.Add(Controller);
}

void UNBSharedTeamList::DeReregisterController(ANBAIController* Controller)
{
	const ANBCharacter* Pawn = Controller->GetPawn<ANBCharacter>();
	if (!Pawn)
	{
		return;
	}

	Controllers.Remove(Controller);
	TeamControllerMap[Pawn->CharacterTeam].Value.Remove(Controller);
}

TArray<ANBAIController*> UNBSharedTeamList::GetAllControllers()
{
	return Controllers;
}

TArray<ANBAIController*> UNBSharedTeamList::GetAllControllersInTeam(const ECharacterTeam Team)
{
	return TeamControllerMap[Team].Value;
}
