// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppUEBlueprintImplementableEventNotImplemented
// ReSharper disable CppUEBlueprintCallableFunctionUnused
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/AIModule/Classes/Perception/AISightTargetInterface.h" 
#include "Characters/NBCharacter.h"
#include "NBSmartObject.generated.h"

class UAIPerceptionStimuliSourceComponent;

UCLASS(Blueprintable, BlueprintType)
class NEONBLADE_API ANBSmartObject : public AActor, public IAISightTargetInterface
{
	GENERATED_BODY()
	
public:	

	ANBSmartObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ANBCharacter> Reserver;

	UFUNCTION(BlueprintPure)
	bool GetIsSmartObjectTaskRunning() const;

	UFUNCTION(BlueprintCallable)
	bool RunSmartObjectTask(ANBCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void FinishSmartObjectTask();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnRunSmartObjectTask();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnFinishSmartObjectTask();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnTickSmartObjectTask();

	UPROPERTY(BlueprintReadOnly)
	bool IsRunning;


#pragma region Smart object reserving

	UFUNCTION(BlueprintPure)
	bool IsSmartObjectReservedBy(ANBCharacter* Character) const;
	
	UFUNCTION(BlueprintPure)
	bool IsSmartObjectReserved() const;
	
	UFUNCTION(BlueprintCallable)
	bool ReserveSmartObject(ANBCharacter* Character);
	
	UFUNCTION(BlueprintCallable)
	bool UnreserveSmartObject(ANBCharacter* Character);
	
#pragma endregion

	UPROPERTY(BlueprintReadOnly)
	float DeltaSeconds;

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool FreeSmartObject(ANBCharacter* Character);

	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, 
	                                                        FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, 
	                                                        float& OutSightStrength, int32* UserData = nullptr, 
	                                                        const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;

};
