// Fill out your copyright notice in the Description page of Project Settings.


#include "NBFunctionLibrary.h"

FVector UNBFunctionLibrary::GetDirectionFromVectorToVector(const FVector& A, const FVector& B)
{
	return (B - A).GetSafeNormal();
}

FVector UNBFunctionLibrary::GetDirectionFromActorToActor(const AActor* A, const AActor* B)
{
	if (!A || !B) return FVector::Zero();
	return GetDirectionFromVectorToVector(A->GetActorLocation(), B->GetActorLocation());
}
