// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/Objects/NBPassiveAbility.h"

#include "Characters/Components/NBAbilitiesComponent.h"

UWorld* UNBPassiveAbility::GetWorld() const
{
	if (Component)
	{
		return Component->GetWorld();
	}
	return nullptr;
}

void UNBPassiveAbility::Initialize(ANBCharacter* AssignedCharacter, UNBAbilitiesComponent* AssignedAbilitiesComponent)
{
	Character = AssignedCharacter;
	Component = AssignedAbilitiesComponent;
}

void UNBPassiveAbility::Tick(const float DeltaSeconds) 
{
	DeltaTime = DeltaSeconds;

	OnTick();
	ReceiveTick();
}

void UNBPassiveAbility::Activate()
{
	OnActivate();
	ReceiveActivate();
}