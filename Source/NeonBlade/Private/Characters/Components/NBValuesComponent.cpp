// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/NBValuesComponent.h"

// Sets default values for this component's properties
UNBValuesComponent::UNBValuesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNBValuesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNBValuesComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNBValuesComponent::AddScalarValue(UNBScalarValue* NewValue)
{
	ScalarValues.Add(NewValue);
}

