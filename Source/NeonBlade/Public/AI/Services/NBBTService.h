// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "NBBTService.generated.h"

class ANBCharacter;
class ANBAIController;

UCLASS(Abstract, Blueprintable)
class NEONBLADE_API UNBBTService : public UBTService
{
	GENERATED_BODY()

public:
	
	UNBBTService(const FObjectInitializer& ObjectInitializer);

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceiveBecomeRelevant();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceiveTick();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceiveCeaseRelevant();

	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* Character;

	UPROPERTY(BlueprintReadOnly)
	ANBAIController* Controller;

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;
};
