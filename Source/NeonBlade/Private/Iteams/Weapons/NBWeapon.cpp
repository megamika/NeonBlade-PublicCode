// Fill out your copyright notice in the Description page of Project Settings.


#include "Iteams/Weapons/NBWeapon.h"

void ANBWeapon::SetNewOwner(ANBCharacter* NewOwner)
{
	OnNewOwnerSet(NewOwner);

	WeaponOwner = NewOwner;
	OnWeaponOwnerSet();
}

void ANBWeapon::SetAsActiveWeapon(const bool Value)
{
	ReceiveSetAsActiveWeapon(Value);
}

bool ANBWeapon::IsOwned() const
{
	return IsValid(WeaponOwner);
}

void ANBWeapon::HoldAction(const int ID)
{
	RecieveHoldAction(ID);
}

void ANBWeapon::ReleaseAction(const int ID)
{
	RecieveReleaseAction(ID);
}

bool ANBWeapon::CanShoot(int ID)
{
	return false;
}
