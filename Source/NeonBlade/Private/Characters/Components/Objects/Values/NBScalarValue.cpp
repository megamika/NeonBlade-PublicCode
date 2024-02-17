// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/Objects/Values/NBScalarValue.h"


void UNBScalarValue::SetupLimits(const float Min, const float Max)
{
    MinValue = Min;
    MaxValue = Max;

    Value = MaxValue;
}

float UNBScalarValue::GetValuePercent() const
{
    return Value/MaxValue;
}

bool UNBScalarValue::GetValueIsAtMinimum() const
{
    return Value <= MinValue;
}

bool UNBScalarValue::GetValueIsAtMaximum() const
{
    return Value >= MaxValue;
}

bool UNBScalarValue::IncreaseValue(float Amount)
{
    Amount = FMath::Abs(Amount);
    if (Value == MaxValue)
    {
        return true;
    }
    Value += Amount;
    Value = FMath::Clamp(Value, MinValue, MaxValue);
    
    if (Value == MaxValue)
    {
        OnMaxValueLimitReached.Broadcast();
    }

    return true;
}

bool UNBScalarValue::DecreaseValue(float Amount)
{
    Amount = FMath::Abs(Amount);
    if (Value == MinValue)
    {
        return true;
    }
    Value -= Amount;
    Value = FMath::Clamp(Value, MinValue, MaxValue);

    if (Value == MinValue)
    {
        OnMinValueLimitReached.Broadcast();
    }

    return true;
}
