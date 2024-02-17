// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Spawning/NBSpawnDomain.h"

#include "AI/Spawning/NBSpawnPoint.h"

// Sets default values
ANBSpawnDomain::ANBSpawnDomain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANBSpawnDomain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANBSpawnDomain::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANBSpawnDomain::SpawnAll()
{
	AllSpawnPoints.Remove(nullptr);

	for (ANBSpawnPoint* SpawnPoint : AllSpawnPoints)
	{
		SpawnPoint->Spawn();
	}
}