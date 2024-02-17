// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "NBAIPerception.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UCLASS()
class NEONBLADE_API UNBAIPerception : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void OnRegister() override;
	
	UFUNCTION(BlueprintCallable)
	void DrawDebugs();
	
	void DrawSightDebug(const UAISenseConfig_Sight* Config) const;

	void DrawHearingDebug(const UAISenseConfig_Hearing* Config) const;

};
