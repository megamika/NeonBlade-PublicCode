// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Iteams/Weapons/NBWeapon.h"
#include "Objects/NBFiringMode.h"

#include "NBBulletWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletHit, FHitResult, Hit);

USTRUCT(Blueprintable)
struct FFiringMode 
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, float> BoneDamageMultipliers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxContiniousShots = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireCooldown = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool InfiniteMagazine = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (editcondition = "InfiniteMagazine == false"))
	int MagazineCapacity = 16;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TracesInAShot = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector Spread = FVector(1.5f, 1.5f, 1.5f);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	TSubclassOf<UNBFiringMode> FiringMode;
};

UCLASS()
class NEONBLADE_API ANBBulletWeapon : public ANBWeapon
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int, FFiringMode> FiringModes;

	UPROPERTY(BlueprintReadOnly)
	TMap<int, UNBFiringMode*> FiringModeObjects;
	

	virtual void HoldAction(int ID) override;

	virtual void ReleaseAction(int ID) override;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	float ModifyDamageForBone(int ID, FName BoneName, float Damage);

	void PerformShot(int ID, float DeltaTime);

	virtual bool CanShoot(int ID) override;

	UPROPERTY(BlueprintReadWrite)
	bool IsReloading;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReloadWeapon();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CancelReloadWeapon();

	UFUNCTION(BlueprintCallable)
	void FillUpMagazineAmmo(int ID);

	UFUNCTION(BlueprintPure)
	UNBFiringMode* GetBulletFiringModeData(int ID, FFiringMode& OutStaticData, bool& OutFound);

	UPROPERTY(BlueprintAssignable)
	FOnShot OnShot;

	UPROPERTY(BlueprintAssignable)
	FOnBulletHit OnBulletHit;

	FVector GetShootDirection() const;

	FVector GetShootOrigin() const;


	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	FVector GetWeaponShootDirection();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	FVector GetWeaponShootOrigin();
};
