// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Memory/Personal/MemorySlots/NBHearingMemorySlot.h"

#include "AI/Controller/Perception/NBAIPerception.h"

void UNBHearingMemorySlot::OnInitialized()
{
	NoiseTypesMap.Add(Combat, FNoiseCollection());
	NoiseTypesMap.Add(Distraction, FNoiseCollection());
	NoiseTypesMap.Add(Footstep, FNoiseCollection());
}

void UNBHearingMemorySlot::UpdateHeardActors(TArray<AActor*> UpdatedActors)
{
	const UNBAIPerception* Perception = Controller->NBPerceptionComponent.Get();
	
	NoiseTypesMap[Combat].NoiseDataMap.Empty();
	NoiseTypesMap[Distraction].NoiseDataMap.Empty();
	NoiseTypesMap[Footstep].NoiseDataMap.Empty();

	for (AActor* HeardActor : UpdatedActors)
	{
		if (HeardActor == Character)
		{
			continue;
		}


		for (const FActorPerceptionInfo* PerceptionInfo = Perception->GetActorInfo(*HeardActor); FAIStimulus Stimulus : PerceptionInfo->LastSensedStimuli)
		{
			const ENBNoiseType NoiseType = UNBAIFunctionLibrary::GetNoiseTypeFromName(Stimulus.Tag);
			if (NoiseType == None) continue;

			NoiseTypesMap[NoiseType].NoiseDataMap.Add(Stimulus.StimulusLocation, FNoiseData{ HeardActor });
		}
	}
}

// ReSharper disable once CppPassValueParameterByConstReference
FNoiseData UNBHearingMemorySlot::GetNoiseDataFromLocation(const FVector Location, const ENBNoiseType NoiseType, bool& OutSucess)
{
	if (!NoiseTypesMap[NoiseType].NoiseDataMap.Contains(Location))
	{
		OutSucess = false;
		return FNoiseData();
	}
	return NoiseTypesMap[NoiseType].NoiseDataMap[Location];
}

TArray<FVector> UNBHearingMemorySlot::GetAllNoiseLocationsForNoiseType(const ENBNoiseType NoiseType)
{
	TArray<FVector> Keys;
	NoiseTypesMap[NoiseType].NoiseDataMap.GetKeys(Keys);
	return Keys;
}

