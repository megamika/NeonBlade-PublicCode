// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/NBTTActivateAbilityOfClass.h"

#include "Characters/Components/NBAbilitiesComponent.h"

UNBTTActivateAbilityOfClass::UNBTTActivateAbilityOfClass(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Activate Ability Of Class";
}

EBTNodeResult::Type UNBTTActivateAbilityOfClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Ability = Character->Abilities->GetAbilityOfClass(AbilityClass);
	if (!Ability)
	{
		return EBTNodeResult::Failed;
	}

	AbilitySucceeded = Ability->TryActivate();

	if (!AbilitySucceeded)
	{
		if (KeepActivatingTaskIfFailed)
		{
			TaskActivatingTimeLeft = KeepTryingTheTaskForTimeAfterFailing;
			return EBTNodeResult::InProgress;
		}

		return FailTaskIfAbilityFailed ? EBTNodeResult::Failed : EBTNodeResult::Succeeded;
	}

	TaskSucessTimeLeft = WaitTimeAfterSucess;
	return EBTNodeResult::InProgress;
}

void UNBTTActivateAbilityOfClass::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!AbilitySucceeded)
	{
		if (KeepActivatingTaskIfFailed)
		{
			TaskActivatingTimeLeft -= DeltaSeconds;
			AbilitySucceeded = Ability->TryActivate();
			if (TaskActivatingTimeLeft <= 0.0f && !AbilitySucceeded)
			{
				FinishLatentTask(OwnerComp, FailTaskIfAbilityFailed ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
			}

			if (AbilitySucceeded)
			{
				TaskSucessTimeLeft = WaitTimeAfterSucess;
			}
		}
	}
	else
	{
		if (WaitUnrillTaskCompletedAfterSucessfillyActivatingIt)
		{
			if (!Ability->GetIsActive())
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
		else if (WaitAfterTaskSucess)
		{
			TaskSucessTimeLeft -= DeltaTime;
			if (TaskSucessTimeLeft <= 0.0f)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}

void UNBTTActivateAbilityOfClass::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	const EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	if (CancelAbilityOnFinish)
	{
		Ability->Cancel();
	}
}
