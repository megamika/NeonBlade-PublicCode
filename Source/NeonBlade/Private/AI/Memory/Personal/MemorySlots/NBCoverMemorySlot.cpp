// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Memory/Personal/MemorySlots/NBCoverMemorySlot.h"

#include "Subsystems/Cover/NBCoverPoint.h"

void UNBCoverMemorySlot::ReserveCover(ANBCoverPoint* Cover)
{
	if (ReservedCover)
	{
		ReservedCover->Release();
	}
	ReservedCover = Cover;
	Cover->Reserve(Character);
}

void UNBCoverMemorySlot::ReleaseCover()
{
	ReservedCover->Release();
	ReservedCover = nullptr;
}

void UNBCoverMemorySlot::AddCoverPointToHistory(ANBCoverPoint* CoverPoint)
{
	CoverHistory.Add(CoverPoint);
	if (CoverHistory.Num() > MaxCoverHistorySize)
	{
		CoverHistory.RemoveAt(0);
	}
}

bool UNBCoverMemorySlot::HasRecentlyVisitedThisCoverPoint(ANBCoverPoint* CoverPoint) const
{
	return CoverHistory.Contains(CoverPoint);
}
