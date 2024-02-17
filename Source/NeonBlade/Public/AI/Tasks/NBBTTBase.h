// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NBBTTBase.generated.h"

class ANBCharacter;
class ANBAIController;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class NEONBLADE_API UNBBTTBase : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UNBBTTBase(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveVariablesAssigned();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveExecute();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveTick();


	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveAbort();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFinish();

	UFUNCTION(BlueprintCallable)
	void FinishExecute(bool bSuccess) const;

	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* Character;

	UPROPERTY(BlueprintReadOnly)
	ANBAIController* Controller;

	UPROPERTY(BlueprintReadOnly)
	float DeltaTime;
};
