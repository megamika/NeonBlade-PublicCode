// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NBCharacter.h"

#include "Characters/Components/NBWeaponsComponent.h"
#include "Characters/Components/NBAbilitiesComponent.h"
#include "Characters/Components/Objects/Values/NBScalarValue.h"
#include "AI/Controller/NBAIController.h"
#include "Subsystems/Barks/NBBarksComponent.h"
#include "Characters/Components/NBValuesComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Characters/Components/NBCharacterMovementComponent.h"

// Sets default values
ANBCharacter::ANBCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	NBMovementComponent = Cast<UNBCharacterMovementComponent>(ACharacter::GetMovementComponent());
	Weapons = CreateDefaultSubobject<UNBWeaponsComponent>(FName("Weapons"));
	Abilities = CreateDefaultSubobject<UNBAbilitiesComponent>(FName("Abilities"));
	Values = CreateDefaultSubobject<UNBValuesComponent>(FName("Values"));
	Barks = CreateDefaultSubobject<UNBBarksComponent>(FName("Barks"));
}

void ANBCharacter::SetUnloaded(const bool Value)
{
	SetActorHiddenInGame(Value);
	Weapons->SetAllWeaponsHidden(Value);

	if (ANBAIController* AIController = GetController<ANBAIController>())
	{
		AIController->SetBrainLocked(Value);
	}
}

UAISense_Sight::EVisibilityResult ANBCharacter::CanBeSeenFrom(const FCanBeSeenFromContext& Context,
		FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested,
		float& OutSightStrength, int32* UserData,
		const FOnPendingVisibilityQueryProcessedDelegate* Delegate)
{
	UWorld* World = GetWorld();

	for (FName VisibleBone : AISightVisibleBones)
	{
		FVector ObservedLocation = Context.ObserverLocation;
		FVector BoneLocation = GetMesh()->GetSocketLocation(VisibleBone);
		FCollisionQueryParams Params = FCollisionQueryParams();
		Params.AddIgnoredActor(Context.IgnoreActor);
		FHitResult Hit;
		World->LineTraceSingleByChannel(Hit, ObservedLocation, BoneLocation, ECC_Visibility, Params);

		if (Hit.GetActor() == this)
		{
			return UAISense_Sight::EVisibilityResult::Visible;
		}
	}

	return UAISense_Sight::EVisibilityResult::NotVisible;
}

void ANBCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	BlueprintGetActorEyesViewPoint(OutLocation, OutRotation);
}

void ANBCharacter::BlueprintGetActorEyesViewPoint_Implementation(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetActorLocation();
	OutRotation = GetActorRotation();
}

// Called when the game starts or when spawned
void ANBCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = NewObject<UNBScalarValue>();
	Health->SetupLimits(0.0f, MaxHealth);
	Values->AddScalarValue(Health);

	Health->OnMinValueLimitReached.AddDynamic(this, &ANBCharacter::Death);

	OnTakeAnyDamage.AddDynamic(this, &ANBCharacter::AnyDamage);
}

// Called every frame
void ANBCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANBCharacter::Death()
{
	if (ANBAIController* AIController = GetController<ANBAIController>())
	{
		AIController->SetBrainLocked(true);
	}

	Abilities->SetAllAbilitiesBlocked(true);
	ReceivedDeath();
}

void ANBCharacter::AnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health->DecreaseValue(Damage);
}

bool ANBCharacter::GetIsDead() const
{
	if (!Health)
	{
		return false;
	}
	return Health->GetValueIsAtMinimum();
}

