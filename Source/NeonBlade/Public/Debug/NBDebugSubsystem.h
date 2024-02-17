// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NBDebugSubsystem.generated.h"



UCLASS()
class NEONBLADE_API UNBDebugSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	TSet<FString> ActiveDebugTags;

public:

	bool IsDebugTagActive(const FString& Tag) const;

	void MakeDebugTagActive(const FString& Tag);
	void MakeDebugTagInactive(const FString& Tag);


};
