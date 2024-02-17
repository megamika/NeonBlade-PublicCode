// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/NBThrowableComponent.h"

// Sets default values for this component's properties
UNBThrowableComponent::UNBThrowableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNBThrowableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNBThrowableComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FVector> UNBThrowableComponent::SimulateGrenadeThrow(FVector Origin, FVector Direction,
	const TArray<AActor*> IgnoredActors) const
{
	Direction.Normalize();
	TArray<FVector> Result = TArray<FVector>();
	const UWorld* World = GetWorld();
	if (!World)
	{
		return Result;
	}

	FVector CurrentOrigin = Origin;
	FVector CurrentDirection = Direction;
	Result.Add(FVector(Origin));

	int i = 0;
	bool Done = false;

	while (!Done && i < 5000)
	{
		bool Hit;
		DoNextSimulationTrace(IgnoredActors, CurrentOrigin, CurrentDirection, Hit,
			CurrentOrigin, CurrentDirection);
		i++;
		if (Hit)
		{
			Result.Add(FVector(CurrentOrigin));
			Done = true;
		}
		else
		{
			Result.Add(FVector(CurrentOrigin));
		}
	}

	return Result;
}

void UNBThrowableComponent::DoNextSimulationTrace(TArray<AActor*> IgnoredActors, FVector Origin, FVector Direction,
	bool& OutHit, FVector& OutNextOrigin, FVector& OutNextDirection) const
{
	UWorld* World = GetWorld();

	FHitResult Hit;
	FVector CurrentDirection = Direction + FVector::DownVector * 0.1f;
	CurrentDirection.Normalize();

	FVector End = Origin + CurrentDirection * 100.0f;
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActors(IgnoredActors);
	World->LineTraceSingleByChannel(Hit, Origin, End, ECC_WorldStatic, Params);

	OutHit = Hit.bBlockingHit;
	OutNextOrigin = OutHit ? Hit.Location : End;
	OutNextDirection = CurrentDirection;
}

