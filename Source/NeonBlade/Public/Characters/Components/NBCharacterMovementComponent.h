// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NBCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum ERotationType
{
	StaySame,
	OrientToMovement,
	OrientToControlRotation,
	RootMotionOnly
};

UENUM(BlueprintType)
enum EMovementType
{
	Default,
	RMOnly
};

UCLASS()
class NEONBLADE_API UNBCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<ERotationType> RotationType;
	
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EMovementType> MovementType;
	
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<ERotationType> RotationTypeOverride;
	UPROPERTY(BlueprintReadWrite)
	bool EnableRotationTypeOverride;
	
	UPROPERTY(BlueprintReadWrite)
	FRotator OrientToMovementRotationModifier;

	UFUNCTION(BlueprintPure)
	ERotationType GetCurrentRotationType() const;

	FRotator DesirdRotation;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDesiredRotation(float DeltaTime);

	void UpdateRotationRate();

	void RotateUpdatedComponent(float DeltaTime);

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* RotationRateOverRotationDiferrence;

	UPROPERTY(BlueprintReadOnly)
	FRotator InitialRotationRate;
};
