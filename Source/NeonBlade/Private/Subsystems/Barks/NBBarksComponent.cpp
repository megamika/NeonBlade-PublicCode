// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Barks/NBBarksComponent.h"

#include "Components/AudioComponent.h"
#include "Characters/NBCharacter.h"
#include "Subsystems/Barks/NBBarksSubsystem.h"

#include "Debug/NBDebugLibrary.h"
#include "Debug/NBDebugTags.h"




// Sets default values for this component's properties
UNBBarksComponent::UNBBarksComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNBBarksComponent::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent = Cast<UAudioComponent>(GetOwner()->AddComponentByClass(UAudioComponent::StaticClass(), false, FTransform::Identity, false));
	Barker = GetOwner<ANBCharacter>();
}


// Called every frame
void UNBBarksComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UNBBarksComponent::PlayBark(const FString BarkName)
{
	if (!Barks.Contains(BarkName)) return false;

	FBark BarkData = Barks[BarkName];

	const UWorld* World = GetWorld();
	if (!World) return false;

	UNBBarksSubsystem* BarksSubsystem = World->GetSubsystem<UNBBarksSubsystem>();
	if (!BarksSubsystem) return false;

	if (BarkData.SinglePersonBark)
	{
		if (BarksSubsystem->IsBarkReservedByAnyone(Barker, BarkName)) return false;
		BarksSubsystem->ReserveBark(Barker, BarkName, 1.5f);
	}

	if (!BarkData.ResponseBarks.IsEmpty()) 
	{
		UNBDebugLibrary::NBPrint(this, UNBDebugTags::DebugTag_Barks(), Barker->GetName() + FString(L" - Sent Respondable Bark: ") + BarkName, FName(*BarkName));

		if (PlayResponseBarkSender(BarkName)) return true;
	}

	if (BarkData.RegularVariations.IsEmpty()) return false;
	if (!AudioComponent) return false;
	USoundBase* RandomBark = BarkData.RegularVariations[FMath::RandRange(0, BarkData.RegularVariations.Num()-1)];
	PlayBarkBasic(RandomBark);

	UNBDebugLibrary::NBPrint(this, UNBDebugTags::DebugTag_Barks(), Barker->GetName() + FString(L" - Played Single Bark: ") + BarkName);

	return true;
}

bool UNBBarksComponent::PlayResponseBarkSender(const FString& BarkName)
{
	const UNBBarksSubsystem* BarksSubsystem = GetBarkSubsystem();

	const ANBCharacter* Responder = BarksSubsystem->GetClosestBarkResponder(Barker);
	if (!Responder) return false;
	
	UNBBarksComponent* BarkComponent = Responder->Barks.Get();
	
	FBark BarkData = Barks[BarkName];
	const FResponseBark RandomResponseBark = BarkData.ResponseBarks[FMath::RandRange(0, BarkData.ResponseBarks.Num()-1)];
	
	PlayBarkBasic(RandomResponseBark.Bark);
	const float BarkDuration = RandomResponseBark.Bark->GetDuration();

	BarkComponent->PlayResponseBarkReceiver(RandomResponseBark, BarkDuration);
	return true;
}

bool UNBBarksComponent::PlayResponseBarkReceiver(const FResponseBark ResponseBark, const float InitialBarkDuration)
{
	CurrentResponseBarkSound = ResponseBark.Response;
	GetWorld()->GetTimerManager().SetTimer(ResponseBarkTimer, this, &UNBBarksComponent::PlayBasicResponseBark, InitialBarkDuration, false);
	return true;
}

void UNBBarksComponent::PlayBasicResponseBark() const
{
	if (Interrupted) return;
	if (!CurrentResponseBarkSound) return;
	PlayBarkBasic(CurrentResponseBarkSound);

	UNBDebugLibrary::NBPrint(this, UNBDebugTags::DebugTag_Barks(), Barker->GetName() + FString(L" - Played Response Bark: ") + CurrentResponseBarkSound->GetName());
}

void UNBBarksComponent::PlayBarkBasic(USoundBase* Sound) const
{
	if (Interrupted) return;
	AudioComponent->SetSound(Sound);
	AudioComponent->Play(0.0f);
}

UNBBarksSubsystem* UNBBarksComponent::GetBarkSubsystem() const
{
	return GetWorld()->GetSubsystem<UNBBarksSubsystem>();
}

void UNBBarksComponent::FreeMyBark()
{

}

void UNBBarksComponent::InterruptAllBarks()
{
	AudioComponent->Stop();
	AudioComponent->SetActive(false);
	Interrupted = true;
}