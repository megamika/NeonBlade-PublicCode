// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Memory/Personal/NBAIMemoryComponent.h"

#include "AI/Memory/Personal/MemorySlots/NBMemorySlot.h"


// Sets default values for this component's properties
UNBAIMemoryComponent::UNBAIMemoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UNBAIMemoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UNBAIMemoryComponent::Initialize(ANBAIController* AssignedController, ANBCharacter* AssignedCharacter)
{
	Controller = AssignedController;
	Character = AssignedCharacter;
}


// Called every frame
void UNBAIMemoryComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNBAIMemoryComponent::AddMemorySlot(UNBMemorySlot* NewMemorySlot) const
{
	NewMemorySlot->Initialize(Character, Controller);
}

