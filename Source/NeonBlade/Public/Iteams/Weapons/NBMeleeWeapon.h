// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Iteams/Weapons/NBWeapon.h"
#include "NBMeleeWeapon.generated.h"

class UAnimMontage;
class UNBMeleeWeaponDamageBox;

USTRUCT(BlueprintType)
struct FMeleeAttack
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> DamageTags;
};

USTRUCT()
struct FDamageBoxes
{
	GENERATED_BODY()

	TSet<UNBMeleeWeaponDamageBox*> Value;
};

/**
 * 
 */
UCLASS()
class NEONBLADE_API ANBMeleeWeapon : public ANBWeapon
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void StartDamaging();
	
	UFUNCTION(BlueprintCallable)
	void StopDamaging();

	UPROPERTY(EditDefaultsOnly)
	TArray<FMeleeAttack> AttackMontages;

	virtual void HoldAction(int ID) override;

	virtual void ReleaseAction(int ID) override {}
	
	bool IsMeleeAttacking();
	
	virtual void OnWeaponOwnerSet() override;

private:
	
	int CurrentAttackID;

	TMap<FName, FDamageBoxes> DamageBoxMap;

	void IndexDamageBoxes();
	
};
