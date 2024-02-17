// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NBFiringMode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class NEONBLADE_API UNBFiringMode : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadOnly)
	bool IsHeldDown;

	UPROPERTY(BlueprintReadOnly)
	int ContiniousShotsPerformed;

	UPROPERTY(BlueprintReadOnly)
	int MagazineAmmoLeft;

	UPROPERTY(BlueprintReadOnly)
	float FireCooldownTimeLeft;

	void ResetForShootStart();
};
