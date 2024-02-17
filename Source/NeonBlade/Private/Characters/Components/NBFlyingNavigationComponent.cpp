// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/NBFlyingNavigationComponent.h"
#include "Characters/NBCharacter.h"
#include "NBFunctionLibrary.h"

// Sets default values for this component's properties
UNBFlyingNavigationComponent::UNBFlyingNavigationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNBFlyingNavigationComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ANBCharacter>(GetOwner());

	TraceDirections.Add(FVector::ForwardVector);
	TraceDirections.Add(FVector::BackwardVector);

	TraceDirections.Add(FVector::LeftVector);
	TraceDirections.Add(FVector::RightVector);

	TraceDirections.Add(FVector::UpVector);
	TraceDirections.Add(FVector::DownVector);

	TraceDirections.Add((FVector::ForwardVector + FVector::RightVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::ForwardVector + FVector::LeftVector).GetUnsafeNormal());

	TraceDirections.Add((FVector::BackwardVector + FVector::RightVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::BackwardVector + FVector::LeftVector).GetUnsafeNormal());

	TraceDirections.Add((FVector::UpVector + FVector::RightVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::UpVector + FVector::LeftVector).GetUnsafeNormal());

	TraceDirections.Add((FVector::DownVector + FVector::RightVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::DownVector + FVector::LeftVector).GetUnsafeNormal());

	TraceDirections.Add((FVector::UpVector + FVector::RightVector + FVector::ForwardVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::UpVector + FVector::LeftVector + FVector::ForwardVector).GetUnsafeNormal());
	
	TraceDirections.Add((FVector::UpVector + FVector::RightVector + FVector::BackwardVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::UpVector + FVector::LeftVector + FVector::BackwardVector).GetUnsafeNormal());

	TraceDirections.Add((FVector::DownVector + FVector::RightVector + FVector::ForwardVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::DownVector + FVector::LeftVector + FVector::ForwardVector).GetUnsafeNormal());

	TraceDirections.Add((FVector::DownVector + FVector::RightVector + FVector::BackwardVector).GetUnsafeNormal());
	TraceDirections.Add((FVector::DownVector + FVector::LeftVector + FVector::BackwardVector).GetUnsafeNormal());
}


// Called every frame
void UNBFlyingNavigationComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	MoveTowardsDestination(DeltaTime);
}



void UNBFlyingNavigationComponent::FlyingTraces()
{
	UWorld* World = GetWorld();
	if (!OwnerCharacter) return;
	if (!World) return;

	AvailibleDirections.Empty();

	for (FVector Direction : TraceDirections)
	{
		FVector Origin = OwnerCharacter->GetActorLocation();
		FVector Dir = Origin + OwnerCharacter->GetActorRotation().RotateVector(Direction) * FlyingNavigationTraceLength;

		FHitResult Hit;
		FCollisionQueryParams Params = FCollisionQueryParams();
		Params.AddIgnoredActor(OwnerCharacter);
		World->LineTraceSingleByChannel(Hit, Origin, Dir, ECC_Visibility, Params);

		if (DrawFlyingTraces)
		{
			DrawDebugLine( GetWorld(), Origin, Dir, Hit.bBlockingHit ? FColor::Green : FColor::Red, false);
		}
		
		if (!Hit.bBlockingHit)
		{
			AvailibleDirections.Add(Direction);
		}
	}
}

void UNBFlyingNavigationComponent::MoveTowardsDestination(float DeltaTime)
{
	if (!DestinationIsActive) return;

	
	FVector MoveDirection = UNBFunctionLibrary::GetDirectionFromVectorToVector(OwnerCharacter->GetActorLocation(), CurrentDestination.Location);

	FlyingTraces();

	MoveDirection = DetermineBestDirection(MoveDirection);

	const float DistanceToDestination = FVector::Dist(OwnerCharacter->GetActorLocation(), CurrentDestination.Location);

	if (DrawDestination)
	{
		DrawDebugSphere(GetWorld(), CurrentDestination.Location, CurrentDestination.AcceptanceRadius, 8, FColor::Purple);
		DrawDebugLine(GetWorld(), OwnerCharacter->GetActorLocation(), CurrentDestination.Location, FColor::Purple);
	}

	if (DistanceToDestination < CurrentDestination.AcceptanceRadius)
	{
		OwnerCharacter->ConsumeMovementInputVector();
		DestinationIsActive = false;
	}
	else
	{
		OwnerCharacter->AddMovementInput(MoveDirection);
	}
}

bool UNBFlyingNavigationComponent::DetermineIfDestinationIsReachable(const FVector& Destination) const
{
	const UWorld* World = GetWorld();
	if (!World) return false;

	const FCollisionQueryParams Params(SCENE_QUERY_STAT(DetermineIfDestinationIsReachable), false);
	TArray<FOverlapResult> Overlaps;
	const FCollisionObjectQueryParams ObjectParams = FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllStaticObjects);

	const bool Hit = World->OverlapMultiByObjectType(Overlaps, Destination, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(OverlapCheckRadius), Params);

	return !Hit;
}

FVector UNBFlyingNavigationComponent::TryCorrectPointToBeReachable(FVector Destination) const
{
	if (DetermineIfDestinationIsReachable(Destination)) 
		return Destination;
	Destination += FVector::UpVector * 151.0f;
	if (DetermineIfDestinationIsReachable(Destination)) 
		return Destination;
	return Destination;
}

bool UNBFlyingNavigationComponent::MoveTo(FDestinationData Destination, bool CorrectDestinationIfUnreachable)
{
	if (CorrectDestinationIfUnreachable)
	{
		Destination.Location = TryCorrectPointToBeReachable(Destination.Location);
	}

	const bool IsReachable = DetermineIfDestinationIsReachable(Destination.Location);
	if (!IsReachable) return false;

	CurrentDestination = Destination;
	DestinationIsActive = true;
	return true;
}

bool UNBFlyingNavigationComponent::IsMovingToDestination() const
{
	return DestinationIsActive;
}

FVector UNBFlyingNavigationComponent::DetermineBestDirection(const FVector& DesiredDirection)
{
	FVector Result = FVector::Zero();

	float MaxDot = -100.0f;
	for (FVector Direction : AvailibleDirections)
	{
		const float Dot = DesiredDirection.Dot(Direction);
		if (Dot > MaxDot)
		{
			MaxDot = Dot;
			Result = Direction;
		}
	}

	return Result;
}


