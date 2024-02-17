// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Tasks/NBBTTBase.h"
#include "Characters/Components/Objects/NBAbility.h"

#include "NBTTActivateAbilityOfClass.generated.h"



UCLASS()
class NEONBLADE_API UNBTTActivateAbilityOfClass : public UNBBTTBase
{
	GENERATED_BODY()

	UNBTTActivateAbilityOfClass(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNBAbility> AbilityClass;

	UPROPERTY(EditAnywhere, Category = "Settings|Sucess Result")
	bool FailTaskIfAbilityFailed = false;

	UPROPERTY(EditAnywhere, Category = "Settings|Keep Activating If Failed")
	bool KeepActivatingTaskIfFailed = false;

	UPROPERTY(EditAnywhere, meta = (editcondition = KeepActivatingTaskIfFailed), Category = "Settings|Keep Activating If Failed")
	float KeepTryingTheTaskForTimeAfterFailing = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Task Sucess Wait", meta = (editcondition = "!WaitUnrillTaskCompletedAfterSucessfillyActivatingIt"))
	bool WaitAfterTaskSucess = false;

	UPROPERTY(EditAnywhere, meta = (editcondition = "WaitAfterTaskSucess && !WaitUnrillTaskCompletedAfterSucessfillyActivatingIt"), Category = "Settings|Task Sucess Wait")
	float WaitTimeAfterSucess = 1.0f;

	float TaskSucessTimeLeft = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Cancel")
	bool CancelAbilityOnFinish = true;

	bool AbilitySucceeded = false;

	float TaskActivatingTimeLeft = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Task Sucess Wait")
	bool WaitUnrillTaskCompletedAfterSucessfillyActivatingIt = true;

	UPROPERTY()
	TObjectPtr<UNBAbility> Ability;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
};
