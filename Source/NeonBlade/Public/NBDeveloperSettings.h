// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GenericTeamAgentInterface.h"
#include "Characters/NBCharacter.h"
#include "NBDeveloperSettings.generated.h"

USTRUCT(Blueprintable)
struct FRelationshipMap 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, config, Category = "AI|Teams")
	TMap<ECharacterTeam, TEnumAsByte<ETeamAttitude::Type>> TeamAttitudes;
};

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Neon Blade"))
class NEONBLADE_API UNBDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, config, Category = "AI|Teams")
	TMap<ECharacterTeam, FRelationshipMap> TeamRelationshipMap;
};
