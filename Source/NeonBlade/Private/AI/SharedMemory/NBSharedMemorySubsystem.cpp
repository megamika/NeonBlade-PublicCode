// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SharedMemory/NBSharedMemorySubsystem.h"

#include "AI/SharedMemory/MemorySlots/NBSharedMemorySlot.h"
#include "AI/SharedMemory/MemorySlots/NBSharedSight.h"

void UNBSharedMemorySubsystem::OnWorldBeginPlay(UWorld& InWorld)
{

}

void UNBSharedMemorySubsystem::PostInitialize()
{
	SharedTeamMemorySlot = NewObject<UNBSharedTeamList>();
	AddMemorySlot(SharedTeamMemorySlot);

	SharedTeamSight = NewObject<UNBSharedSight>();
	AddMemorySlot(SharedTeamSight);

	SharedSearch = NewObject<UNBSharedSearch>();
	AddMemorySlot(SharedSearch);
}

void UNBSharedMemorySubsystem::AddMemorySlot(UNBSharedMemorySlot* NewSlot)
{
	if (!IsValid(NewSlot)) return;
	NewSlot->Initialize(this);
	TeamSlotMap.Add(NewSlot);
}

