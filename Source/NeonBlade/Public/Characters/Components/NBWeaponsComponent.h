// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Iteams/Weapons/NBWeapon.h>
#include <Characters/NBCharacter.h>

#include "NBWeaponsComponent.generated.h"

USTRUCT(Blueprintable)
struct FWeaponData 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ANBWeapon* Weapon;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentWeaponChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBWeaponsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNBWeaponsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetAllWeaponsHidden(bool Value);

	UFUNCTION(BlueprintCallable)
	bool SetCurrentWeapon(int Value);

	bool SocketWeapon(const int NewSlot);

	UFUNCTION(BlueprintCallable)
	bool AddWeaponToInventory(ANBWeapon* Weapon, int Slot);

	UFUNCTION(BlueprintPure)
	ANBWeapon* GetCurrentWeaponActor();

	UFUNCTION(BlueprintPure)
	int GetCurrentWeaponIndex() const;

	UFUNCTION(BlueprintCallable)
	void HoldDownCurrentWeapon(int ID);

	UFUNCTION(BlueprintCallable)
	void ReleaseCurrentWeapon(int ID);

	UPROPERTY()
	TObjectPtr<ANBCharacter> NBCharacter;

	int CurrentWeapon;

	UPROPERTY(BlueprintReadWrite)
	TMap<int, FWeaponData> WeaponMap;

	UPROPERTY(BlueprintAssignable)
	FOnCurrentWeaponChanged OnCurrentWeaponChanged;

	UPROPERTY(EditDefaultsOnly)
	bool PrintWhenCurrentWeaponChanged;

};
