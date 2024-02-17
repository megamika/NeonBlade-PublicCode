// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NBBarksComponent.generated.h"

class ANBCharacter;
class UAudioComponent;
class USoundBase;
class UNBBarksSubsystem;

USTRUCT(BlueprintType)
struct FResponseBark
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> Bark;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> Response;
};

USTRUCT(BlueprintType)
struct FBark 
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	bool SinglePersonBark;

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<USoundBase>> RegularVariations;

	UPROPERTY(EditDefaultsOnly)
	TArray<FResponseBark> ResponseBarks;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEONBLADE_API UNBBarksComponent : public UActorComponent
{
	GENERATED_BODY()

	UNBBarksSubsystem* GetBarkSubsystem() const;

	bool Interrupted;

public:	
	// Sets default values for this component's properties
	UNBBarksComponent();
	
	UPROPERTY()
	TObjectPtr<ANBCharacter> Barker;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, FBark> Barks;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TObjectPtr<UAudioComponent> AudioComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FString LastSingleBark;
	UFUNCTION(BlueprintCallable)
	bool PlayBark(FString BarkName);

	static void FreeMyBark();

	bool PlayResponseBarkSender(const FString& BarkName);

	FTimerHandle MyBarkTimer;
	FTimerHandle ResponseBarkTimer;
	FTimerHandle ReserveBarkTimer;

	UPROPERTY()
	TObjectPtr<USoundBase> CurrentResponseBarkSound;
	
	bool PlayResponseBarkReceiver(FResponseBark ResponseBark, float InitialBarkDuration);
	void PlayBasicResponseBark() const;

	void PlayBarkBasic(USoundBase* Sound) const;

	UFUNCTION(BlueprintCallable)
	void InterruptAllBarks();

};
