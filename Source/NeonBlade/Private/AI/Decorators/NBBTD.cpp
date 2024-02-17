// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/NBBTD.h"

#include "Characters/NBCharacter.h"
#include "AI/Controller/NBAIController.h"

UNBBTD::UNBBTD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UNBBTD::PostInitProperties()
{
	Super::PostInitProperties();
	bNotifyBecomeRelevant = true;
}

void UNBBTD::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	Controller = OwnerComp.GetOwner<ANBAIController>();
	if (Controller)
	{
		Character = Controller->GetPawn<ANBCharacter>();
	}
	ReceiveOnAssignedReferences();

	ReceiveOnBecomeRelevant();
}

bool UNBBTD::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UNBBTD* MyNode = const_cast<UNBBTD*>(this);
	MyNode->OnBecomeRelevant(OwnerComp, NodeMemory);
	return MyNode->PerformConditionCheck();
}

void UNBBTD::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
	DeltaTime = DeltaSeconds;
	ReceiveTick();
	ConditionalFlowAbort(OwnerComp, EBTDecoratorAbortRequest::ConditionResultChanged);
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
