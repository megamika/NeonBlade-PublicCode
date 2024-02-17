// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppPossiblyUninitializedMember
#include "Characters/Components/NBWeaponsComponent.h"


// Sets default values for this component's properties
UNBWeaponsComponent::UNBWeaponsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNBWeaponsComponent::BeginPlay()
{
	Super::BeginPlay();

	NBCharacter = GetOwner<ANBCharacter>();
}


// Called every frame
void UNBWeaponsComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNBWeaponsComponent::SetAllWeaponsHidden(const bool Value)
{
	TSet<int> AllWeaponSlots;
	WeaponMap.GetKeys(AllWeaponSlots);

	for (const int Slot : AllWeaponSlots)
	{
		if (!WeaponMap[Slot].Weapon) continue;
		WeaponMap[Slot].Weapon->SetHidden(Value);
	}
}

bool UNBWeaponsComponent::SetCurrentWeapon(const int Value)
{
	if (!WeaponMap.Contains(Value))
	{
		return false;
	}
	
	SocketWeapon(Value);

	CurrentWeapon = Value;
	OnCurrentWeaponChanged.Broadcast();

	return true;
}

bool UNBWeaponsComponent::SocketWeapon(const int NewSlot)
{
	if (!WeaponMap.Contains(NewSlot))
	{
		return false;
	}

	ANBWeapon* NewWeapon = WeaponMap[NewSlot].Weapon;
	if (!NewWeapon)
	{
		return false;
	}

	TSet<int> WeaponSlots;
	WeaponMap.GetKeys(WeaponSlots);
	WeaponSlots.Remove(NewSlot);

	for (const int WeaponSlot : WeaponSlots)
	{
		if (!WeaponMap[WeaponSlot].Weapon)
		{
			continue;	
		}
		WeaponMap[WeaponSlot].Weapon->SetAsActiveWeapon(false);
	}

	NewWeapon->SetAsActiveWeapon(true);
	return true;
}

bool UNBWeaponsComponent::AddWeaponToInventory(ANBWeapon* Weapon, const int Slot)
{
	if (!Weapon) return false;

	if (WeaponMap.Contains(Slot))
	{
		return false;
	}

	WeaponMap.Add(Slot, FWeaponData{ Weapon });
	Weapon->SetNewOwner(NBCharacter);

	SetCurrentWeapon(CurrentWeapon);
	
	return true;
}

ANBWeapon* UNBWeaponsComponent::GetCurrentWeaponActor()
{
	if (!WeaponMap.Contains(CurrentWeapon)) {
		return nullptr;
	}

	return WeaponMap[CurrentWeapon].Weapon;
}

int UNBWeaponsComponent::GetCurrentWeaponIndex() const
{
	return CurrentWeapon;
}

void UNBWeaponsComponent::HoldDownCurrentWeapon(const int ID)
{
	if (ANBWeapon* CurrentWeaponActor = GetCurrentWeaponActor())
	{
		CurrentWeaponActor->HoldAction(ID);
	}
}

void UNBWeaponsComponent::ReleaseCurrentWeapon(const int ID)
{
	if (ANBWeapon* CurrentWeaponActor = GetCurrentWeaponActor())
	{
		CurrentWeaponActor->ReleaseAction(ID);
	}
}


