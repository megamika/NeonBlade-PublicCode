// Fill out your copyright notice in the Description page of Project Settings.


#include "NBAIFunctionLibrary.h"

#include "NBDeveloperSettings.h"

ETeamAttitude::Type UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(const ANBCharacter* From, const ANBCharacter* To)
{
	if (!From || !To)
	{
		return ETeamAttitude::Type::Neutral;
	}
	const UNBDeveloperSettings* Settings = GetDefault<UNBDeveloperSettings>();
	const TMap<ECharacterTeam, FRelationshipMap>& RelationshipMap = Settings->TeamRelationshipMap;
	const ECharacterTeam FromTeam = From->CharacterTeam;
	const ECharacterTeam ToTeam = To->CharacterTeam;

	if (RelationshipMap.Contains(FromTeam))
	{
		if (RelationshipMap[FromTeam].TeamAttitudes.Contains(ToTeam))
		{
			return RelationshipMap[FromTeam].TeamAttitudes[ToTeam];
		}
	}

	return ETeamAttitude::Type::Neutral;
}

FName UNBAIFunctionLibrary::GetNoiseTypeName(const ENBNoiseType NoiseType)	
{
	switch (NoiseType)
	{
	case Distraction:
		return FName("Distraction");
	case Combat:
		return FName("Combat");
	case Footstep:
		return FName("Footstep");
	default:
		return FName("NaN");
	}
}

ENBNoiseType UNBAIFunctionLibrary::GetNoiseTypeFromName(const FName Name)
{
	if (Name == FName("Distraction"))
	{
		return Distraction;
	}
	if (Name == FName("Combat"))
	{
		return Combat;
	}
	if (Name == FName("Footstep"))
	{
		return Footstep;
	}
	return None;
}

bool UNBAIFunctionLibrary::IsValidAliveCharacter(const TObjectPtr<ANBCharacter> Character)
{
	if (!IsValid(Character)) return false;
	if (Character->GetIsDead()) return false;
	return true;
}