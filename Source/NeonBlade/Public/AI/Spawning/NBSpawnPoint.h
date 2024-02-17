// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBSpawnPoint.generated.h"

class ANBCharacter;

UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API ANBSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANBSpawnPoint();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANBCharacter> CharacterToSpawn;

	TSet<ANBCharacter*> SpawnedCharacters;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ANBCharacter* Spawn();

};
