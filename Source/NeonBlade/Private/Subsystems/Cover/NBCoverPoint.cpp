// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Cover/NBCoverPoint.h"

#include "Characters/NBCharacter.h"
#include "Subsystems/Cover/NBCoverSubsystem.h"

// Sets default values
ANBCoverPoint::ANBCoverPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

bool ANBCoverPoint::IsReserved() const
{
	return IsValid(Reserver);
}

void ANBCoverPoint::Reserve(ANBCharacter* NewReserver)
{
	Reserver = NewReserver;
}

void ANBCoverPoint::Release()
{
	Reserver = nullptr;
}

// Called when the game starts or when spawned
void ANBCoverPoint::BeginPlay()
{
	Super::BeginPlay();
	CoverSubsystem = GetWorld()->GetSubsystem<UNBCoverSubsystem>();
	CoverSubsystem->RegisterCoverPoint(this);
}

// Called every frame
void ANBCoverPoint::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

