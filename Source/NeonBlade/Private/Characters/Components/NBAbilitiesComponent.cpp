// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/NBAbilitiesComponent.h"

#include "Characters/NBCharacter.h"

// Sets default values for this component's properties
UNBAbilitiesComponent::UNBAbilitiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNBAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = GetOwner<ANBCharacter>();
	
}

void UNBAbilitiesComponent::TickComponent(const float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (AllAbilitiesAreBlocked)
	{
		return;
	}

	for (UNBPassiveAbility* PassiveAbility : PassiveAbilities)
	{
		PassiveAbility->Tick(DeltaTime);
	}

	for (UNBAbility* Ability : Abilities)
	{
		if (!Ability->GetIsActive()) continue;
		Ability->DeltaTime = DeltaTime;
		Ability->Tick();
		Ability->ReceiveTick();
	}
}


void UNBAbilitiesComponent::AddPassiveAbility(UNBPassiveAbility* NewPassiveAbility)
{
	if (!NewPassiveAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewPassiveAbility is Null"));
		return;
	}

	NewPassiveAbility->Initialize(Character, this);
	PassiveAbilities.AddUnique(NewPassiveAbility);
	NewPassiveAbility->Activate();
}

void UNBAbilitiesComponent::AddAbility(UNBAbility* NewAbility)
{
	if (!NewAbility)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewAbility is Null"));
		return;
	}

	NewAbility->Initialize(Character, this);
	Abilities.AddUnique(NewAbility);
}

void UNBAbilitiesComponent::CancelAllAbilities()
{
	for (UNBAbility* Ability : Abilities) 
	{
		if (Ability->GetIsActive())
		{
			Ability->Cancel();
		}
	}
}

void UNBAbilitiesComponent::SetAllAbilitiesBlocked(bool Value)
{
	if (Value)
	{
		CancelAllAbilities();
	}
	AllAbilitiesAreBlocked = Value;
}

UNBAbility* UNBAbilitiesComponent::GetAbilityOfClass(TSubclassOf<UNBAbility> AbilityClass)
{
	for (UNBAbility* Ability : Abilities)
	{
		const UClass* CurrentAbilityClass = Ability->GetClass();
		if (CurrentAbilityClass == AbilityClass)
		{
			return Ability;
		}
	}

	return nullptr;
}

bool UNBAbilitiesComponent::TryActivateAbilityOfClass(TSubclassOf<UNBAbility> AbilityClass)
{
	for (UNBAbility* Ability : Abilities)
	{
		const UClass* CurrentAbilityClass = Ability->GetClass();
		if (CurrentAbilityClass == AbilityClass)
		{
			return Ability->TryActivate();
		}
	}

	return false;
}

bool UNBAbilitiesComponent::TryCancelAbilityOfClass(TSubclassOf<UNBAbility> AbilityClass)
{

	for (UNBAbility* Ability : Abilities)
	{
		const UClass* CurrentAbilityClass = Ability->GetClass();
		if (CurrentAbilityClass == AbilityClass)
		{
			Ability->Cancel();
			return true;
		}
	}

	return false;
}



