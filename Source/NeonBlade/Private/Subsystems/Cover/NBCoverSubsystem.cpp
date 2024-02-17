// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppPassValueParameterByConstReference
#include "Subsystems/Cover/NBCoverSubsystem.h"

#include "Subsystems/Cover/NBCoverPoint.h"
#include "NBFunctionLibrary.h"

void UNBCoverSubsystem::RegisterCoverPoint(ANBCoverPoint* CoverPoint)
{
	CoverPoints.Add(CoverPoint);
}

ANBCoverPoint* UNBCoverSubsystem::GetClosestCoverPoint(const FVector Location, const FVector TargetLocation,
	const TArray<ANBCoverPoint*>& ExcludedCoverPoints, const float CutoffDistance)
{
	float MinDistance = CutoffDistance * 2.0f;
	ANBCoverPoint* Result = nullptr;

	for (ANBCoverPoint* CoverPoint : CoverPoints)
	{
		if (ExcludedCoverPoints.Contains(CoverPoint))
		{
			continue;
		}

		if (CoverPoint->IsReserved())
		{
			continue;
		}

		const float Distance = FVector::Distance(CoverPoint->GetActorLocation(), Location);
		if (Distance > CutoffDistance)
		{
			continue;
		}

		if (!IsCoverSafeAgainstTarget(CoverPoint, TargetLocation))
		{
			continue;
		}

		if (Distance < MinDistance)
		{
			Result = CoverPoint;
			MinDistance = Distance;
		}
	}

	return Result;
}

bool UNBCoverSubsystem::IsCoverSafeAgainstTarget(const ANBCoverPoint* CoverPoint, FVector TargetLocation, const float MinDotProduct)
{
	const FVector ToTargetDirection = UNBFunctionLibrary::GetDirectionFromVectorToVector(CoverPoint->GetActorLocation(), TargetLocation);
	const FVector CoverDirection = CoverPoint->GetActorForwardVector();

	// ReSharper disable once CppTooWideScopeInitStatement
	const float DotProduct = FVector::DotProduct(CoverDirection, ToTargetDirection);
	if (DotProduct < MinDotProduct)
	{
		return false;
	}

	return true;
}


