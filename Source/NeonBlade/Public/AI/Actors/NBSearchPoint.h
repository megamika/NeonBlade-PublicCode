// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBSearchPoint.generated.h"

class ANBCharacter;

UCLASS(BlueprintType, Blueprintable)
class NEONBLADE_API ANBSearchPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANBSearchPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool Reserve(ANBCharacter* Character);
	
	UFUNCTION(BlueprintCallable)
	bool Release(ANBCharacter* Character);
	
	UFUNCTION(BlueprintPure)
	ANBCharacter* GetReserver() const { return Reserver; }

	UFUNCTION(BlueprintPure)
	bool IsReserved() const;

private:

	TObjectPtr<ANBCharacter> Reserver;

};
