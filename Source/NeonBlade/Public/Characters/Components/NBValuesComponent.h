// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NBValuesComponent.generated.h"

class UNBScalarValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBValuesComponent : public UActorComponent
{
	GENERATED_BODY()

	TSet<UNBScalarValue*> ScalarValues;

public:	
	// Sets default values for this component's properties
	UNBValuesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddScalarValue(UNBScalarValue* NewValue);
		
};
