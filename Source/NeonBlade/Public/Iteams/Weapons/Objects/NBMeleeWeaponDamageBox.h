// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "NBMeleeWeaponDamageBox.generated.h"

class ANBCharacter;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API UNBMeleeWeaponDamageBox : public UBoxComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	FName DamageTag;
	
	void SetCurrentDamage(float Value);
	
	void StartDamaging();

	void StopDamaging();

private:

	TObjectPtr<ANBCharacter> OwnerCharacter;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	float CurrentDamage = 10.0f;

	bool IsDamaging = false;
};
