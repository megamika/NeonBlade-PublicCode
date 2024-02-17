// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NBThrowableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBThrowableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNBThrowableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TArray<FVector> SimulateGrenadeThrow(FVector Origin, FVector Direction, TArray<AActor*> IgnoredActors) const;
	
	void DoNextSimulationTrace(TArray<AActor*> IgnoredActors, FVector Origin, FVector Direction, bool& OutHit,
		FVector& OutNextOrigin, FVector& OutNextDirection) const;
};
