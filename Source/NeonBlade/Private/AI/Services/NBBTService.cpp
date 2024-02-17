// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/NBBTService.h"

#include "Characters/NBCharacter.h"
#include "AI/Controller/NBAIController.h"

UNBBTService::UNBBTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	bTickIntervals = true;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;

	bCreateNodeInstance = true;

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UNBBTService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	Controller = OwnerComp.GetOwner<ANBAIController>();
	if (Controller)
	{
		Character = Controller->GetPawn<ANBCharacter>();
	}

	OnReceiveBecomeRelevant();
}

void UNBBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	DeltaTime = DeltaSeconds;
	OnReceiveTick();
}

void UNBBTService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	OnReceiveCeaseRelevant();
}
