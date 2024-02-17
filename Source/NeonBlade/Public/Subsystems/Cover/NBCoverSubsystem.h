// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NBCoverSubsystem.generated.h"

class ANBCoverPoint;
class ANBAIController;
class ANBCharacter;

UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API UNBCoverSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	TSet<ANBCoverPoint*> CoverPoints;

	void RegisterCoverPoint(ANBCoverPoint* CoverPoint);

	UFUNCTION(BlueprintPure)
	ANBCoverPoint* GetClosestCoverPoint(const FVector Location, const FVector TargetLocation, const TArray<ANBCoverPoint*>& ExcludedCoverPoints,
		const float CutoffDistance = 10000.0f);

	UFUNCTION(BlueprintPure)
	static bool IsCoverSafeAgainstTarget(const ANBCoverPoint* CoverPoint, FVector TargetLocation, const float MinDotProduct = 0.5f);
};
