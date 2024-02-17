// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Actors/NBSearchPoint.h"

#include "NBAIFunctionLibrary.h"
#include "AI/SharedMemory/NBSharedMemorySubsystem.h"

// Sets default values
ANBSearchPoint::ANBSearchPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ANBSearchPoint::BeginPlay()
{
	Super::BeginPlay();

	const UNBSharedMemorySubsystem* SharedMemory = GetWorld()->GetSubsystem<UNBSharedMemorySubsystem>();
	SharedMemory->SharedSearch->RegisterSearchPoint(this);
}

// Called every frame
void ANBSearchPoint::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ANBSearchPoint::Reserve(ANBCharacter* Character)
{
	if (IsReserved()) return false;
	Reserver = Character;
	return true;
}

bool ANBSearchPoint::Release(ANBCharacter* Character)
{
	if (Reserver == Character)
	{
		Reserver = nullptr;
		return true;
	}
	return false;
}

bool ANBSearchPoint::IsReserved() const
{
	const bool IsReserverValid = UNBAIFunctionLibrary::IsValidAliveCharacter(Reserver);
	return IsReserverValid;
}
