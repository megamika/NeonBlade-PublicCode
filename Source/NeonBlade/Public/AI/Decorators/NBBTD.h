// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppUEBlueprintImplementableEventNotImplemented
// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "NBBTD.generated.h"

class ANBCharacter;
class ANBAIController;

UCLASS(Abstract, Blueprintable)
class NEONBLADE_API UNBBTD : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* Character;

	UPROPERTY(BlueprintReadOnly)
	ANBAIController* Controller;

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;

	UNBBTD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintImplementableEvent)
	bool PerformConditionCheck();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnAssignedReferences();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnBecomeRelevant();


	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveTick();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
