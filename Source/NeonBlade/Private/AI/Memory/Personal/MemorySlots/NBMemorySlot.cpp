// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Memory/Personal/MemorySlots/NBMemorySlot.h"

void UNBMemorySlot::Initialize(ANBCharacter* AssignedCharacter, ANBAIController* AssignedController)
{
	Character = AssignedCharacter;
	Controller = AssignedController;
	OnInitialized();
	ReceiveInitialized();
}

UWorld* UNBMemorySlot::GetWorld() const
{
	if (Character)
	{
		return Character->GetWorld();
	}

	return nullptr;
}

void UNBMemorySlot::OnInitialized()
{

}
