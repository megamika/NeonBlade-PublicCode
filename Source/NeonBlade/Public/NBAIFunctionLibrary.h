// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Characters/NBCharacter.h"

#include "NBAIFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum ENBNoiseType 
{
	Distraction,
	Combat,
	Footstep,
	None
};

/**
 * 
 */
UCLASS()
class NEONBLADE_API UNBAIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
		static ETeamAttitude::Type GetAttitudeTowardsCharacter(const ANBCharacter* From, const ANBCharacter* To);

	UFUNCTION(BlueprintPure, Category = "Sound Tags")
		static FName GetNoiseTypeName(ENBNoiseType NoiseType);

	UFUNCTION(BlueprintPure, Category = "Sound Tags")
		static ENBNoiseType GetNoiseTypeFromName(FName Name);

	static bool IsValidAliveCharacter(TObjectPtr<ANBCharacter> Character);
};
