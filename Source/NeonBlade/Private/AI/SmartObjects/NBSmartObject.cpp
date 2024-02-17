// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SmartObjects/NBSmartObject.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ANBSmartObject::ANBSmartObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(FName("Stimuli"));
}

// Called when the game starts or when spawned
void ANBSmartObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANBSmartObject::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ANBSmartObject::RunSmartObjectTask(ANBCharacter* Character)
{
	if (!IsSmartObjectReservedBy(Character)) return false;

	IsRunning = true;
	ReceiveOnRunSmartObjectTask();
	return true;
}

void ANBSmartObject::FinishSmartObjectTask()
{
	IsRunning = false;
	ReceiveOnFinishSmartObjectTask();
}

bool ANBSmartObject::IsSmartObjectReservedBy(ANBCharacter* Character) const
{
	return Reserver == Character;
}

bool ANBSmartObject::IsSmartObjectReserved() const
{
	return IsValid(Reserver);
}

bool ANBSmartObject::ReserveSmartObject(ANBCharacter* Character)
{
	if (IsSmartObjectReserved()) return false;

	Reserver = Character;
	return true;
}

bool ANBSmartObject::UnreserveSmartObject(ANBCharacter* Character)
{
	if (!IsSmartObjectReservedBy(Character)) return false;

	Reserver = nullptr;
	return true;
}

bool ANBSmartObject::GetIsSmartObjectTaskRunning() const
{
	return IsRunning;
}

void ANBSmartObject::TickActor(const float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	DeltaSeconds = DeltaTime;
	if (IsRunning)
	{
		ReceiveOnTickSmartObjectTask();
	}
}

bool ANBSmartObject::FreeSmartObject(ANBCharacter* Character)
{
	if (!IsSmartObjectReservedBy(Character)) return false;

	Destroy();
	return true;
}

UAISense_Sight::EVisibilityResult ANBSmartObject::CanBeSeenFrom(const FCanBeSeenFromContext& Context,
                                                                FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested,
                                                                float& OutSightStrength, int32* UserData,
                                                                const FOnPendingVisibilityQueryProcessedDelegate* Delegate)
{
	UWorld* World = GetWorld();

	FVector ObservedLocation = Context.ObserverLocation;
	FVector MyLocation = GetActorLocation();
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.AddIgnoredActor(Context.IgnoreActor);
	FHitResult Hit;
	World->LineTraceSingleByChannel(Hit, ObservedLocation, MyLocation, ECC_Visibility, Params);

	if (!Hit.bBlockingHit)
	{
		return UAISense_Sight::EVisibilityResult::Visible;
	}

	return UAISense_Sight::EVisibilityResult::NotVisible;
}