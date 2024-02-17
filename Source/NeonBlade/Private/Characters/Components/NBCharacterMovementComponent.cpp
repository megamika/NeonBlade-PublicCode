// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/NBCharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

void UNBCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitialRotationRate = RotationRate;


}

ERotationType UNBCharacterMovementComponent::GetCurrentRotationType() const
{
	if (EnableRotationTypeOverride)
	{
		return RotationTypeOverride;
	}

	return RotationType;
}


void UNBCharacterMovementComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (MovementType == RMOnly)
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		return;
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bUseControllerDesiredRotation = false;
	bOrientRotationToMovement = false;

	SetDesiredRotation(DeltaTime);
	UpdateRotationRate();

	RotateUpdatedComponent(DeltaTime);

}


void UNBCharacterMovementComponent::SetDesiredRotation(const float DeltaTime)
{
	const FRotator CurrentRotaton = UpdatedComponent->GetComponentRotation();
	DesirdRotation = CurrentRotaton;
	FRotator DeltaRot = GetDeltaRotation(DeltaTime);

	const AController* Controller = GetController();

	const ERotationType FinalRotationType = GetCurrentRotationType();

	if (Controller)
	{

		switch (FinalRotationType)
		{
		case StaySame:
			DesirdRotation = CurrentRotaton;
			break;
		case OrientToMovement:
			DesirdRotation = ComputeOrientToMovementRotation(CurrentRotaton, DeltaTime, DeltaRot);
			DesirdRotation = UKismetMathLibrary::ComposeRotators(DesirdRotation, OrientToMovementRotationModifier);
			break;
		case OrientToControlRotation:
			DesirdRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
			break;
		default:
			DesirdRotation = CurrentRotaton;
			break;
		}
	}
}

void UNBCharacterMovementComponent::UpdateRotationRate()
{
	const AController* Controller = GetController();
	if (RotationRateOverRotationDiferrence && Controller)
	{
		const FRotator CurrentRotaton = UpdatedComponent->GetComponentRotation();

		const FRotator CurrentTodesiredDelta = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotaton, DesirdRotation);

		const float RotRateMultiplier = RotationRateOverRotationDiferrence->GetFloatValue(FMath::Abs(CurrentTodesiredDelta.Yaw));

		RotationRate = InitialRotationRate * RotRateMultiplier;
	}
}

void UNBCharacterMovementComponent::RotateUpdatedComponent(float DeltaTime)
{
	const FRotator CurrentRotaton = UpdatedComponent->GetComponentRotation();

	const FRotator SetRotation = UKismetMathLibrary::RInterpTo_Constant(CurrentRotaton, DesirdRotation, DeltaTime, RotationRate.Yaw);

	MoveUpdatedComponent(FVector::ZeroVector, SetRotation, false);
}

