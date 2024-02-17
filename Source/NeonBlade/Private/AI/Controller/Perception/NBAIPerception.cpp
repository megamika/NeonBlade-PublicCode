// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/Perception/NBAIPerception.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "AIController.h"

void UNBAIPerception::BeginPlay()
{
	Super::BeginPlay();
}

void UNBAIPerception::OnRegister()
{
	Super::OnRegister();
}

void UNBAIPerception::DrawDebugs()
{
	for (TObjectPtr<UAISenseConfig> SenseConfig : SensesConfig)
	{
		if (const UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(SenseConfig))
		{
			DrawSightDebug(SightConfig);
			continue;
		}

		if (const UAISenseConfig_Hearing* HearingConfig = Cast<UAISenseConfig_Hearing>(SenseConfig))
		{
			DrawHearingDebug(HearingConfig);
		}
	}
}

void UNBAIPerception::DrawSightDebug(const UAISenseConfig_Sight* Config) const
{
	const AActor* Pawn = GetOwner<AAIController>()->GetPawn();
	if (!Pawn)
	{
		return;
	}
	FVector Origin;
	FRotator DirectionRot;
	Pawn->GetActorEyesViewPoint(Origin, DirectionRot);

	for (size_t i = 0; i < 30; i++)
	{
		float Alpha = i / 30.0f;
		const float Angle = FMath::Lerp(-Config->PeripheralVisionAngleDegrees, Config->PeripheralVisionAngleDegrees, Alpha);
		UE_LOG(LogTemp, Log, TEXT("Alhpa: %f"), Angle);
		FVector CurDirection = FRotator(0.0f,Angle, 0.0f)
		.RotateVector(FVector::ForwardVector);
		CurDirection = DirectionRot.RotateVector(CurDirection);

		DrawDebugLine(GetWorld(), Origin, Origin + CurDirection * Config->SightRadius, FColor::Purple, false, 0.1f);
	}


}

void UNBAIPerception::DrawHearingDebug(const UAISenseConfig_Hearing* Config) const
{
	const AActor* Pawn = GetOwner<AAIController>()->GetPawn();
	if (!Pawn)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), Config->HearingRange, 16, FColor::Yellow, false, 0.1f);
	
	
}
