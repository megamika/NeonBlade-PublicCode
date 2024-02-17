// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NBSpawnDomain.generated.h"

class ANBSpawnPoint;
class ANBCharacter;

UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API ANBSpawnDomain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANBSpawnDomain();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ANBSpawnPoint*> AllSpawnPoints;

	UFUNCTION(BlueprintCallable)
	void SpawnAll();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
