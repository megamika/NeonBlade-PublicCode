// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NBFlyingNavigationComponent.generated.h"

class ANBCharacter;

USTRUCT(BlueprintType)
struct FDestinationData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector Location;

	UPROPERTY(BlueprintReadWrite)
	float AcceptanceRadius;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBFlyingNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FlyingTraces")
	float FlyingNavigationTraceLength = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
	bool DrawFlyingTraces = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
	bool DrawDestination = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug")
	float OverlapCheckRadius = 35.0f;

	// Sets default values for this component's properties
	UNBFlyingNavigationComponent();

	TObjectPtr<ANBCharacter> OwnerCharacter;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void FlyingTraces();
	
	FVector DetermineBestDirection(const FVector& DesiredDirection);
	
	void MoveTowardsDestination(float DeltaTime);


	bool DetermineIfDestinationIsReachable(const FVector& Destination) const;

	FVector TryCorrectPointToBeReachable(FVector Destination) const;

	UFUNCTION(BlueprintCallable)
	bool MoveTo(FDestinationData Destination, bool CorrectDestinationIfUnreachable = false);

	UFUNCTION(BlueprintPure)
	bool IsMovingToDestination() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	TArray<FVector> TraceDirections;
	TArray<FVector> AvailibleDirections;

	bool DestinationIsActive;
	FDestinationData CurrentDestination;


};
