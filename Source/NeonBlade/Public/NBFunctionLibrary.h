// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NBFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NEONBLADE_API UNBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static FVector GetDirectionFromVectorToVector(const FVector& A, const FVector& B);
	
	UFUNCTION(BlueprintPure)
	static FVector GetDirectionFromActorToActor(const AActor* A, const AActor* B);
};
