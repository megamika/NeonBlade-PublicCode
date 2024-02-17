// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppPossiblyUninitializedMember
#include "AI/Services/NBBTSActivateAbilityOfClass.h"

#include "Characters/Components/NBAbilitiesComponent.h"

UNBBTSActivateAbilityOfClass::UNBBTSActivateAbilityOfClass(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Activate Ability Of Class";
}

void UNBBTSActivateAbilityOfClass::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	Ability = Character->Abilities->GetAbilityOfClass(AbilityClass);

	Ability->TryActivate();
}

void UNBBTSActivateAbilityOfClass::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (KeepTryingToActivateEveryFrame)
	{
		if (!Ability->GetIsActive())
		{
			Ability->TryActivate();
		}
	}
}

void UNBBTSActivateAbilityOfClass::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	Ability->Cancel();
}
