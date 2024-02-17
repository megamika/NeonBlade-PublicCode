// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/Objects/NBAbility.h"

#include "Characters/Components/NBAbilitiesComponent.h"

void UNBAbility::Initialize(ANBCharacter* AssignedCharacter, UNBAbilitiesComponent* AssignedComponent)
{
	Character = AssignedCharacter;
	Component = AssignedComponent;
	OnValuesSet();
}

bool UNBAbility::CheckIfBlockedByOtherAbilities()
{
	for (const UNBAbility* Ability : BlockedByAbilities)
	{
		if (Ability->GetIsActive())
		{
			return true;
		}
	}
	return false;
}

bool UNBAbility::CheckIfRquiredAbilitiesAreActive()
{
	if (RequiredActiveAbilities.IsEmpty())
	{
		return false;
	}
	for (const UNBAbility* Ability : RequiredActiveAbilities)
	{
		if (!Ability->GetIsActive())
		{
			return true;
		}
	}
	return false;
}

bool UNBAbility::TryActivate()
{
	if (GetIsActive())
	{
		return true;
	}

	if (CheckIfBlockedByOtherAbilities())
	{
		return false;
	}

	if (CheckIfRquiredAbilitiesAreActive())
	{
		return false;
	}

	if (!K2_CanActivate())
	{
		return false;
	}

	IsActive = true;
	for (UNBAbility* AbilityToBlock : BlocksAbilities) {
		if (AbilityToBlock->GetIsActive())
		{
			AbilityToBlock->Cancel();
		}
	}

	Activation();
	ReceiveActivation();
	OnAbilityActivated.Broadcast();
	return true;
}

void UNBAbility::Cancel()
{
	if (!IsActive)
	{
		return;
	}

	for (UNBAbility* AbilityRequirer : RequiredByAbilities) 
	{
		if (AbilityRequirer->GetIsActive())
		{
			AbilityRequirer->Cancel();
		}
	}

	IsActive = false;
	Cancellation();
	ReceiveCancellation();
	OnAbilityCanceled.Broadcast();
}

void UNBAbility::Activation()
{
}

bool UNBAbility::K2_CanActivate_Implementation()
{
	return true;
}

void UNBAbility::AddBlockedByAbility(UNBAbility* Ability)
{
	BlockedByAbilities.AddUnique(Ability);
	Ability->BlocksAbilities.AddUnique(this);

	if (IsActive)
	{
		if (CheckIfBlockedByOtherAbilities())
		{
			Cancel();
		}
	}

}

void UNBAbility::AddRequiredActiveAbility(UNBAbility* Ability)
{
	RequiredActiveAbilities.AddUnique(Ability);
	Ability->RequiredByAbilities.AddUnique(this);

	if (IsActive)
	{
		if (CheckIfRquiredAbilitiesAreActive())
		{
			Cancel();
		}
	}
}

void UNBAbility::Cancellation()
{
}

UWorld* UNBAbility::GetWorld() const
{
	if (Component)
	{
		return Component->GetWorld();
	}
	return nullptr;
}


