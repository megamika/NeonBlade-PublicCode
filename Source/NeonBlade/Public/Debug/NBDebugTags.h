// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NBDebugTags.generated.h"

/**
 * 
 */
UCLASS()
class NEONBLADE_API UNBDebugTags : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure)
	static FString DebugTag_Barks()
	{
		return FString(TEXT("Barks"));
	}

};
