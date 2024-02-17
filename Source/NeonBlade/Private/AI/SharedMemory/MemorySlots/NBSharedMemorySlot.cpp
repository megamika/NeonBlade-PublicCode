// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SharedMemory/MemorySlots/NBSharedMemorySlot.h"

#include "AI/SharedMemory/NBSharedMemorySubsystem.h"

UWorld* UNBSharedMemorySlot::GetWorld() const
{
	if (MemorySubsystem)
	{
		return MemorySubsystem->GetWorld();
	}
	return nullptr;
}

void UNBSharedMemorySlot::Initialize(UNBSharedMemorySubsystem* AssignedMemorySubsystem)
{
	MemorySubsystem = AssignedMemorySubsystem;
}
