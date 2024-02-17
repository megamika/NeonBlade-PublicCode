// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/NBAIController.h"

#include "AI/SharedMemory/NBSharedMemorySubsystem.h"
#include "AI/Controller/Perception/NBAIPerception.h"
#include "AI/Memory/Personal/MemorySlots/NBSightMemorySlot.h"
#include "AI/Memory/Personal/MemorySlots/NBHearingMemorySlot.h"
#include "AI/Memory/Personal/MemorySlots/NBCoverMemorySlot.h"
#include "AI/Memory/Personal/MemorySlots/NBSearchMemorySlot.h"
#include "AI/Memory/Personal/NBAIMemoryComponent.h"
#include "Characters/NBCharacter.h"
#include "Navigation/PathFollowingComponent.h"

FPathFollowingRequestResult ANBAIController::MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath)
{
	LastMoveRequest = MoveRequest;
	return Super::MoveTo(MoveRequest, OutPath);
}

void ANBAIController::SetBrainLocked(const bool Value)
{
	BrainLocked = Value;
	ReceiveSetBrainLocked(Value);

	const UWorld* World = GetWorld();
	if (!World) return;

	const UNBSharedMemorySubsystem* SharedMemory = World->GetSubsystem<UNBSharedMemorySubsystem>();
	if (Value) SharedMemory->SharedTeamMemorySlot->DeReregisterController(this);
	else SharedMemory->SharedTeamMemorySlot->RegisterController(this);
}

FVector ANBAIController::GetLastMoveToDestination() const
{
	if (LastMoveRequest.GetGoalActor()) return LastMoveRequest.GetGoalActor()->GetActorLocation();
	return LastMoveRequest.GetGoalLocation();
}

void ANBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	NBCharacter = Cast<ANBCharacter>(InPawn);
	MemoryComponent->Initialize(this, NBCharacter);

	SightMemory = NewObject<UNBSightMemorySlot>();
	MemoryComponent->AddMemorySlot(SightMemory);

	HeardMemory = NewObject<UNBHearingMemorySlot>();
	MemoryComponent->AddMemorySlot(HeardMemory);

	CoverMemory = NewObject<UNBCoverMemorySlot>();
	MemoryComponent->AddMemorySlot(CoverMemory);

	SearchMemory = NewObject<UNBSearchMemorySlot>();
	MemoryComponent->AddMemorySlot(SearchMemory);
	
	if (const UWorld* World = GetWorld())
	{
		const UNBSharedMemorySubsystem* SharedMemorySubsystem = World->GetSubsystem<UNBSharedMemorySubsystem>();
		SharedMemorySubsystem->SharedTeamMemorySlot->RegisterController(this);
	}

	ReceiveOnPosess();
}

void ANBAIController::OnUnPossess()
{
	Super::OnUnPossess();
	if (const UWorld* World = GetWorld())
	{
		const UNBSharedMemorySubsystem* SharedMemorySubsystem = World->GetSubsystem<UNBSharedMemorySubsystem>();
		SharedMemorySubsystem->SharedTeamMemorySlot->DeReregisterController(this);
	}

	ReceiveOnUnPosess();
}

ANBAIController::ANBAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MemoryComponent = CreateDefaultSubobject<UNBAIMemoryComponent>(FName("Memory"));
	NBPerceptionComponent = CreateDefaultSubobject<UNBAIPerception>(FName("Perception"));
	PerceptionComponent = NBPerceptionComponent;
}

void ANBAIController::BeginPlay()
{
	Super::BeginPlay();
}


