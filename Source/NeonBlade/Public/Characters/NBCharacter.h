// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/Perception/AISightTargetInterface.h"

#include "NBCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterTeam : uint8
{
	Player,
	Soldier,
	Allies,
	Undead,
	Last UMETA(Hidden) //Should always be the last member and never assigned as a team
};


UCLASS()
class NEONBLADE_API ANBCharacter : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANBCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void SetUnloaded(bool Value);

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> AISightVisibleBones;

	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, 
		FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, 
			float& OutSightStrength, int32* UserData = nullptr, 
				const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;


	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	UFUNCTION(BlueprintNativeEvent)
	void BlueprintGetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECharacterTeam CharacterTeam;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UNBCharacterMovementComponent> NBMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UNBWeaponsComponent> Weapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UNBAbilitiesComponent> Abilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UNBValuesComponent> Values;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UNBBarksComponent> Barks;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	TObjectPtr<class UNBScalarValue> Health;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	FVector GetFiringOrigin();

	UFUNCTION(BlueprintImplementableEvent)
	FVector GetFiringDirection();

	UFUNCTION()
	void Death();

	UFUNCTION()
	void AnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintPure)
	bool GetIsDead() const;

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivedDeath();

};
