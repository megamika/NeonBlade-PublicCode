// Fill out your copyright notice in the Description page of Project Settings.


#include "Iteams/Weapons/Objects/NBMeleeWeaponDamageBox.h"

#include "Characters/NBCharacter.h"
#include "NBAIFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UNBMeleeWeaponDamageBox::BeginPlay()
{
	OwnerCharacter = Cast<ANBCharacter>(GetOwner());
	if (!OwnerCharacter) return;
	OnComponentBeginOverlap.AddDynamic(this, &UNBMeleeWeaponDamageBox::OnBeginOverlap);
}

void UNBMeleeWeaponDamageBox::StartDamaging()
{
	IsDamaging = true;
}

void UNBMeleeWeaponDamageBox::StopDamaging()
{
	IsDamaging = false;
}

void UNBMeleeWeaponDamageBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!IsDamaging) return;
	if (!OwnerCharacter) return;
	if (OtherActor == GetOwner()) return;

	if (const ANBCharacter* OtherCharacter = Cast<ANBCharacter>(OtherActor))
	{
		const ETeamAttitude::Type Attitude = UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(
			OwnerCharacter, OtherCharacter);
		if (Attitude == ETeamAttitude::Type::Friendly) return;
	}
	
	UGameplayStatics::ApplyDamage(OtherActor, CurrentDamage, OwnerCharacter->GetController(),
		OwnerCharacter, UDamageType::StaticClass());
}

void UNBMeleeWeaponDamageBox::SetCurrentDamage(const float Value)
{
	CurrentDamage = Value;
}

