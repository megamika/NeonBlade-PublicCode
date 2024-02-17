// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Services/NBBTService.h"
#include "NBBTSActivateAbilityOfClass.generated.h"

class UNBAbility;
/**
 * 
 */
UCLASS()
class NEONBLADE_API UNBBTSActivateAbilityOfClass : public UNBBTService
{
	GENERATED_BODY()

public:

	UNBBTSActivateAbilityOfClass(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNBAbility> AbilityClass;

	UPROPERTY(EditAnywhere)
	bool KeepTryingToActivateEveryFrame;

	UPROPERTY()
	TObjectPtr<UNBAbility> Ability;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
