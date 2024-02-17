// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBCoverPoint.generated.h"

class ANBCharacter;
class UNBCoverSubsystem;

UENUM(BlueprintType)
enum FStandingType
{
	Standing,
	Crouched
};


UENUM(BlueprintType)
enum FLeanType
{
	Left,
	Right,
	Centered
};

UCLASS()
class NEONBLADE_API ANBCoverPoint : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ANBCoverPoint();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<FStandingType> StandingType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<FLeanType> LeaningType;

	UPROPERTY()
	TObjectPtr<ANBCharacter> Reserver;

	bool IsReserved() const;

	UFUNCTION(BlueprintCallable)
	void Reserve(ANBCharacter* NewReserver);

	UFUNCTION(BlueprintCallable)
	void Release();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TObjectPtr<UNBCoverSubsystem> CoverSubsystem;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
