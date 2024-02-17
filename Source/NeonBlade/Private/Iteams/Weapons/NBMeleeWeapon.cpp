// Fill out your copyright notice in the Description page of Project Settings.


#include "Iteams/Weapons/NBMeleeWeapon.h"

#include "Iteams/Weapons/Objects/NBMeleeWeaponDamageBox.h"

void ANBMeleeWeapon::OnWeaponOwnerSet()
{
	IndexDamageBoxes();
}

void ANBMeleeWeapon::StartDamaging()
{
	if (!IsMeleeAttacking())
	{
		StopDamaging();
		return;
	}

	const TArray<FName>& DamageTags = AttackMontages[CurrentAttackID].DamageTags;
	for (FName DamageTag : DamageTags)
	{
		if (!DamageBoxMap.Contains(DamageTag))
		{
			continue;
		}
		const TSet<UNBMeleeWeaponDamageBox*>& DamageBoxes = DamageBoxMap[DamageTag].Value;
		for (UNBMeleeWeaponDamageBox* DamageBox : DamageBoxes)
		{
			DamageBox->StartDamaging();
		}
	}
}

void ANBMeleeWeapon::StopDamaging()
{
	if (!AttackMontages.IsValidIndex(CurrentAttackID)) return;

	const TArray<FName>& DamageTags = AttackMontages[CurrentAttackID].DamageTags;
	for (FName DamageTag : DamageTags)
	{
		if (!DamageBoxMap.Contains(DamageTag))
		{
			continue;
		}
		const TSet<UNBMeleeWeaponDamageBox*>& DamageBoxes = DamageBoxMap[DamageTag].Value;
		for (UNBMeleeWeaponDamageBox* DamageBox : DamageBoxes)
		{
			DamageBox->StopDamaging();
		}
	}
}

void ANBMeleeWeapon::HoldAction(const int ID)
{
	if (!AttackMontages.IsValidIndex(ID)) return;
	if (!AttackMontages[ID].AttackMontage) return;

	WeaponOwner->PlayAnimMontage(AttackMontages[ID].AttackMontage);
	CurrentAttackID = ID;
}

bool ANBMeleeWeapon::IsMeleeAttacking()
{
	if (!WeaponOwner) return false;
	if (!WeaponOwner->GetMesh()->GetAnimInstance()) return false;
	if (!AttackMontages.IsValidIndex(CurrentAttackID)) return false;

	const UAnimMontage* MontageToCheck = AttackMontages[CurrentAttackID].AttackMontage;

	if (!MontageToCheck) return false;

	return WeaponOwner->GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontages[CurrentAttackID].AttackMontage);
}

void ANBMeleeWeapon::IndexDamageBoxes()
{
	DamageBoxMap.Empty();

	TArray<UNBMeleeWeaponDamageBox*> WeaponDamageBoxes;
	WeaponOwner->GetComponents(WeaponDamageBoxes);
	for (UNBMeleeWeaponDamageBox* DamageBox : WeaponDamageBoxes)
	{
		const FName& DamageTag = DamageBox->DamageTag;
		if (!DamageBoxMap.Contains(DamageTag))
		{
			DamageBoxMap.Add(DamageTag, FDamageBoxes());
		}
		DamageBoxMap[DamageTag].Value.Add(DamageBox);
	}
}

