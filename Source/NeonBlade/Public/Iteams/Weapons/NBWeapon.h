// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Iteams/NBIteam.h"
#include "Characters/NBCharacter.h"

#include "NBWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NEONBLADE_API ANBWeapon : public ANBIteam
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* WeaponOwner;

	void SetNewOwner(ANBCharacter* NewOwner);

	virtual void OnWeaponOwnerSet() {}

	void SetAsActiveWeapon(bool Value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveSetAsActiveWeapon(bool Value);

	UFUNCTION(BlueprintPure)
	bool IsOwned() const;

	UFUNCTION(BlueprintCallable)
	virtual void HoldAction(int ID);

	UFUNCTION(BlueprintCallable)
	virtual void ReleaseAction(int ID);

	UFUNCTION(BlueprintPure)
	virtual bool CanShoot(int ID);

	UFUNCTION(BlueprintImplementableEvent)
	void OnNewOwnerSet(ANBCharacter* NewOwner);

	UFUNCTION(BlueprintImplementableEvent)
	void RecieveHoldAction(int ID);

	UFUNCTION(BlueprintImplementableEvent)
	void RecieveReleaseAction(int ID);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StanceTag;
};
