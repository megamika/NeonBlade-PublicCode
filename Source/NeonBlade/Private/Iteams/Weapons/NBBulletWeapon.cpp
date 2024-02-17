	// Fill out your copyright notice in the Description page of Project Settings.


#include "Iteams/Weapons/NBBulletWeapon.h"

#include "Kismet/KismetSystemLibrary.h"
#include "NBAIFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>

void ANBBulletWeapon::HoldAction(const int ID)
{
	if (!FiringModes.Contains(ID))
	{
		return;
	}
	FiringModeObjects[ID]->IsHeldDown = true;
	FiringModeObjects[ID]->ContiniousShotsPerformed = 0;
	FiringModeObjects[ID]->FireCooldownTimeLeft = 0.0f;

	Super::HoldAction(ID);
}

void ANBBulletWeapon::ReleaseAction(const int ID)
{
	if (!FiringModes.Contains(ID))
	{
		return;
	}
	FiringModeObjects[ID]->IsHeldDown = false;
	FiringModeObjects[ID]->ContiniousShotsPerformed = 0;

	Super::ReleaseAction(ID);
}

void ANBBulletWeapon::BeginPlay()
{
	Super::BeginPlay();

	//Initialize firing modes
	for (const TPair<int, FFiringMode>& FiringMode : FiringModes)
	{
		UNBFiringMode* NewFiringMode = NewObject<UNBFiringMode>();
		FiringModeObjects.Add(FiringMode.Key, NewFiringMode);
		NewFiringMode->MagazineAmmoLeft = FiringMode.Value.MagazineCapacity;
	}

}

void ANBBulletWeapon::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!WeaponOwner)
	{
		return;
	}

	for (const TPair<int, FFiringMode>& FM : FiringModes)
	{
		PerformShot(FM.Key, DeltaTime);
	}
}

bool ANBBulletWeapon::CanShoot(const int ID)
{
	const FFiringMode& FiringMode = FiringModes[ID];
	const UNBFiringMode* FiringModeObject = FiringModeObjects[ID];

	const bool EnoughAmmoInMagazine = FiringModeObject->MagazineAmmoLeft <= 0 && FiringMode.MagazineCapacity != -1;
	if (EnoughAmmoInMagazine && !FiringMode.InfiniteMagazine) return false;

	return true;
}

float ANBBulletWeapon::ModifyDamageForBone(const int ID, const FName BoneName, const float Damage)
{
	if (!FiringModes.Contains(ID)) return 0.0f;
	if (!FiringModes[ID].BoneDamageMultipliers.Contains(BoneName)) return Damage;
	return FiringModes[ID].BoneDamageMultipliers[BoneName] * Damage;
}

void ANBBulletWeapon::PerformShot(int ID, float DeltaTime)
{
	FFiringMode& FiringMode = FiringModes[ID];
	UNBFiringMode* FiringModeObject = FiringModeObjects[ID];

	if (!FiringModeObject->IsHeldDown) return;

	if (FiringModeObject->ContiniousShotsPerformed >= FiringMode.MaxContiniousShots && FiringMode.MaxContiniousShots != -1) return;

	FiringModeObject->FireCooldownTimeLeft -= DeltaTime;

	if (FiringModeObject->FireCooldownTimeLeft > 0.0f) return;

	if (FiringModeObject->MagazineAmmoLeft <= 0 && FiringMode.MagazineCapacity != -1) return;

	FiringModeObject->MagazineAmmoLeft -= 1;
	FiringModeObject->ContiniousShotsPerformed += 1;

	FVector Direction = GetShootDirection();
	FVector Origin = GetShootOrigin();
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(WeaponOwner);

	int TracesToPerform = FiringMode.TracesInAShot;
	for (size_t i = 0; i < TracesToPerform; i++)
	{
		FRotator SpreadModifier = FRotator(
			FMath::FRandRange(-FiringMode.Spread.X, FiringMode.Spread.X),
			FMath::FRandRange(-FiringMode.Spread.Y, FiringMode.Spread.Y),
			FMath::FRandRange(-FiringMode.Spread.Z, FiringMode.Spread.Z));
		FVector SpreadDirection = SpreadModifier.RotateVector(Direction);
		FVector End = Origin + SpreadDirection * 10000.0f;

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, Origin, End, ECC_Visibility, CollisionParams);

		if (HitResult.bBlockingHit)
		{
			if (ANBCharacter* HitCharacter = Cast<ANBCharacter>(HitResult.GetActor()))
			{
				ETeamAttitude::Type TeamAttitude = UNBAIFunctionLibrary::GetAttitudeTowardsCharacter(WeaponOwner, HitCharacter);
				if (TeamAttitude == ETeamAttitude::Friendly)
				{
					return;
				}
			}

			AActor* HitActor = HitResult.GetActor();

			float FinalDamage = ModifyDamageForBone(ID, HitResult.BoneName, FiringMode.Damage);

			UGameplayStatics::ApplyPointDamage(HitActor, FinalDamage, WeaponOwner->GetActorForwardVector(), HitResult, WeaponOwner->GetController(), this, FiringMode.DamageType);

			UKismetSystemLibrary::DrawDebugLine(GetWorld(), Origin, HitResult.Location, FColor::Red, 0.2f);
			UKismetSystemLibrary::DrawDebugPoint(GetWorld(), HitResult.Location, 5.6f, FColor::Red, 0.3f);

			OnBulletHit.Broadcast(HitResult);
		}
	}
	FiringModeObject->FireCooldownTimeLeft = FiringMode.FireCooldown;
	OnShot.Broadcast();
}



void ANBBulletWeapon::FillUpMagazineAmmo(const int ID)
{
	if (!FiringModeObjects.Contains(ID))
	{
		return;
	}

	FiringModeObjects[ID]->MagazineAmmoLeft = FiringModes[ID].MagazineCapacity;
}

UNBFiringMode* ANBBulletWeapon::GetBulletFiringModeData(const int ID, FFiringMode& OutStaticData, bool& OutFound)
{
	if (!FiringModes.Contains(ID) || !FiringModeObjects.Contains(ID))
	{
		OutFound = false;
		return nullptr;
	}

	OutStaticData = FiringModes[ID];
	OutFound = true;
	return FiringModeObjects[ID];
}



FVector ANBBulletWeapon::GetShootDirection() const
{
	if (!WeaponOwner)
	{
		return FVector();
	}
	return WeaponOwner->GetFiringDirection().GetSafeNormal();
}

FVector ANBBulletWeapon::GetShootOrigin() const
{
	if (!WeaponOwner)
	{
		return FVector();
	}
	return WeaponOwner->GetFiringOrigin();
}
