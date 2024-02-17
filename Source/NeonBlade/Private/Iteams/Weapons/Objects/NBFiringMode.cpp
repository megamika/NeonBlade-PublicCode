// Fill out your copyright notice in the Description page of Project Settings.


#include "Iteams/Weapons/Objects/NBFiringMode.h"

void UNBFiringMode::ResetForShootStart()
{
	ContiniousShotsPerformed = 0;
	FireCooldownTimeLeft = 0;
}
