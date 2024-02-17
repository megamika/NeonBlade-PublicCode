// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppTooWideScope
#include "AI/SharedMemory/MemorySlots/NBSharedSearch.h"

#include "AI/Actors/NBSearchPoint.h"
#include "Characters/NBCharacter.h"
#include "AI/Controller/NBAIController.h"
#include "AI/Memory/Personal/MemorySlots/NBSearchMemorySlot.h"

void UNBSharedSearch::RegisterSearchPoint(ANBSearchPoint* SearchPoint)
{
	if (!IsValid(SearchPoint)) return;
	SearchPoints.Add(SearchPoint);
}

// ReSharper disable once CppPassValueParameterByConstReference
ANBSearchPoint* UNBSharedSearch::GetBestSearchPoint(const ANBCharacter* Character, const FVector Location, const float CutoffDistance)
{
	if (!IsValid(Character)) return nullptr;

	const ANBAIController* Controller = Character->GetController<ANBAIController>();

	if (!IsValid(Controller)) return nullptr;

	TObjectPtr<ANBSearchPoint> Result;
	float MinDistance = UE_BIG_NUMBER;
	for (TObjectPtr<ANBSearchPoint> SearchPoint : SearchPoints)
	{
		const float Distance = FVector::Dist(Location, SearchPoint->GetActorLocation());
		if (Distance > CutoffDistance) continue;

		if (SearchPoint->IsReserved()) continue;

		const bool SearchPointBeenVisited = Controller->SearchMemory->HasThisSearchPointBeenVisited(SearchPoint);

		if (SearchPointBeenVisited) continue;

		if (Distance < MinDistance)
		{
			Result = SearchPoint;
			MinDistance = Distance;
		}
	}
	return Result;
}
