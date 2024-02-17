// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Memory/Personal/MemorySlots/NBSearchMemorySlot.h"


void UNBSearchMemorySlot::AddSearchPointToHistory(ANBSearchPoint* SearchPoint)
{
	SearchPointHistory.Add(SearchPoint);

	if (SearchPointHistory.Num() > MaxSearchPointHistorySize)
	{
		SearchPointHistory.RemoveAt(0);
	}
}

bool UNBSearchMemorySlot::HasThisSearchPointBeenVisited(ANBSearchPoint* SearchPoint) const
{
	return SearchPointHistory.Contains(SearchPoint);
}
