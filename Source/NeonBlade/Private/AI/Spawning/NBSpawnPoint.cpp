// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Spawning/NBSpawnPoint.h"

#include "Characters/NBCharacter.h"

// Sets default values
ANBSpawnPoint::ANBSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANBSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANBSpawnPoint::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ANBCharacter* ANBSpawnPoint::Spawn()
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();

	ANBCharacter* SpawnedCharacter = World->SpawnActor<ANBCharacter>(CharacterToSpawn, SpawnLocation, SpawnRotation);
	SpawnedCharacters.Add(SpawnedCharacter);
	return SpawnedCharacter;
}