// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Characters/NBCharacter.h"
#include "NBBarksSubsystem.generated.h"

USTRUCT()
struct FSaidBark
{
	GENERATED_BODY()

	TMap<FString, float> UsedBarks;
};

class ANBCharacter;
/**
 * 
 */
UCLASS()
class NEONBLADE_API UNBBarksSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	bool CheckValidity(const ANBCharacter* Character);

public:

	virtual void Tick(float DeltaTime) override;

	TMap<ECharacterTeam, FSaidBark> UsedBarksMap;

	ANBCharacter* GetClosestBarkResponder(const ANBCharacter* Barker) const;
	
	void ReserveBark(const ANBCharacter* Character, const FString& Bark, float Time);
	
	void FreeBark(const ANBCharacter* Character, const FString& Bark);
	
	bool IsBarkReservedByAnyone(const ANBCharacter* Character, const FString Bark);


	virtual ETickableTickType GetTickableTickType() const override;

	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UNBBarksSubsystem, STATGROUP_Tickables); }
};
