// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AI/Controller/NBAIController.h"
#include "NBAIMemoryComponent.generated.h"

class UNBMemorySlot;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBAIMemoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNBAIMemoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void Initialize(ANBAIController* AssignedController, ANBCharacter* AssignedCharacter);

	UPROPERTY()
	TObjectPtr<ANBAIController> Controller;
	UPROPERTY()
	TObjectPtr<ANBCharacter> Character;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	TSet<UNBMemorySlot*> MemorySlots;

	UFUNCTION(BlueprintCallable)
	void AddMemorySlot(UNBMemorySlot* NewMemorySlot) const;
};
