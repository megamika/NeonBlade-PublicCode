// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/NBBTTBase.h"

#include "Characters/NBCharacter.h"
#include "AI/Controller/NBAIController.h"


UNBBTTBase::UNBBTTBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    INIT_TASK_NODE_NOTIFY_FLAGS();
    bNotifyTick = true;
    bNotifyTaskFinished = true;
    bIgnoreRestartSelf = false;
    bTickIntervals = true;

    bCreateNodeInstance = true;
}

EBTNodeResult::Type UNBBTTBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    Controller = OwnerComp.GetOwner<ANBAIController>();
    if (Controller)
    {
        Character = Controller->GetPawn<ANBCharacter>();
    }
	 ReceiveVariablesAssigned();
    ReceiveExecute();
    return EBTNodeResult::InProgress;
}

void UNBBTTBase::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
    ReceiveFinish();
}

void UNBBTTBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    SetNextTickTime(NodeMemory, 0.1f);
    DeltaTime = DeltaSeconds;
    ReceiveTick();
}

EBTNodeResult::Type UNBBTTBase::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::AbortTask(OwnerComp, NodeMemory);
    ReceiveAbort();
    return EBTNodeResult::Aborted;
}

void UNBBTTBase::FinishExecute(const bool bSuccess) const
{
    UBehaviorTreeComponent* OwnerComp = Cast<UBehaviorTreeComponent>(Controller->GetBrainComponent());
    const EBTNodeResult::Type NodeResult(bSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed);
    if (OwnerComp) {
        FinishLatentTask(*OwnerComp, NodeResult);
    }
}
