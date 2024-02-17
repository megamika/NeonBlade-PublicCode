// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppUEBlueprintCallableFunctionUnused
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/Components/Objects/NBAbility.h"
#include "Characters/Components/Objects/NBPassiveAbility.h"
#include "NBAbilitiesComponent.generated.h"

class ANBCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNBAbilitiesComponent();

	UPROPERTY()
	TArray<UNBAbility*> Abilities;
	UPROPERTY()
	TArray<UNBPassiveAbility*> PassiveAbilities;
	
	UPROPERTY(BlueprintReadOnly)
	ANBCharacter* Character;
	
	bool AllAbilitiesAreBlocked;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddPassiveAbility(UNBPassiveAbility* NewPassiveAbility);

	UFUNCTION(BlueprintCallable)
	void AddAbility(UNBAbility* NewAbility);

	UFUNCTION(BlueprintCallable)
	void CancelAllAbilities();

	UFUNCTION(BlueprintCallable)
	void SetAllAbilitiesBlocked(bool Value);


	UFUNCTION(BlueprintPure)
	UNBAbility* GetAbilityOfClass(TSubclassOf<UNBAbility> AbilityClass);

	UFUNCTION(BlueprintCallable)
	bool TryActivateAbilityOfClass(TSubclassOf<UNBAbility> AbilityClass);

	UFUNCTION(BlueprintCallable)
	bool TryCancelAbilityOfClass(TSubclassOf<UNBAbility> AbilityClass);
};
