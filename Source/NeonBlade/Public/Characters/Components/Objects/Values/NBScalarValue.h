// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/Objects/Values/NBValue.h"
#include "NBScalarValue.generated.h"

#define MIN_flt			(1.175494351e-38F)
#define MAX_flt			(3.402823466e+38F)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValueLimitReached);

UCLASS(BlueprintType, Blueprintable)
class NEONBLADE_API UNBScalarValue : public UNBValue
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable)
	void SetupLimits(float Min, float Max);

	float MaxValue = MIN_flt;
	float MinValue = MAX_flt;

	UFUNCTION(BlueprintPure)
	float GetValue() const { return Value; }

	UFUNCTION(BlueprintPure)
	float GetValuePercent() const;

	UFUNCTION(BlueprintPure)
	bool GetValueIsAtMinimum() const;

	UFUNCTION(BlueprintPure)
	bool GetValueIsAtMaximum() const;

	UFUNCTION(BlueprintCallable)
	bool IncreaseValue(float Amount);

	UFUNCTION(BlueprintCallable)
	bool DecreaseValue(float Amount);

	UPROPERTY(BlueprintAssignable)
	FOnValueLimitReached OnMaxValueLimitReached;

	UPROPERTY(BlueprintAssignable)
	FOnValueLimitReached OnMinValueLimitReached;
	
private:
	
	float Value;

};
