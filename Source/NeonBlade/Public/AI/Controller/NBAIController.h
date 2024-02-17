// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NBAIController.generated.h"

struct FPathFollowingRequestResult;

class ANBCharacter;
class UNBSightMemorySlot;
class UNBHearingMemorySlot;

class UNBAIMemoryComponent;
class UNBAIPerception;
class UNBCoverMemorySlot;
class UNBSearchMemorySlot;
/**
 * 
 */
UCLASS()
class NEONBLADE_API ANBAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

public:
	
	ANBAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FAIMoveRequest LastMoveRequest;

	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr) override;

	UPROPERTY(BlueprintReadOnly)
	bool BrainLocked;
	UFUNCTION(BlueprintCallable)
	void SetBrainLocked(bool Value);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveSetBrainLocked(bool Value);

	UFUNCTION(BlueprintPure)
	FVector GetLastMoveToDestination() const;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnPosess();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnUnPosess();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNBAIMemoryComponent> MemoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNBAIPerception> NBPerceptionComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBSightMemorySlot> SightMemory;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBHearingMemorySlot> HeardMemory;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBCoverMemorySlot> CoverMemory;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNBSearchMemorySlot> SearchMemory;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ANBCharacter> NBCharacter;

};
