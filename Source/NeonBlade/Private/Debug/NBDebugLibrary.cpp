// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/NBDebugLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Debug/NBDebugSubsystem.h"

bool UNBDebugLibrary::IsDebugTagActive(const UObject* WorldContextObject, const FString& Tag)
{
	const UNBDebugSubsystem* DS = GetDebugSubsystem(WorldContextObject);
	return DS->IsDebugTagActive(Tag);
	
}

UNBDebugSubsystem* UNBDebugLibrary::GetDebugSubsystem(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UNBDebugSubsystem>();
}

void UNBDebugLibrary::ActivateDebugTag(const UObject* WorldContextObject, const FString Tag)
{
	UNBDebugSubsystem* DS = GetDebugSubsystem(WorldContextObject);
	DS->MakeDebugTagActive(Tag);
}

void UNBDebugLibrary::DeactivateDebugTag(const UObject* WorldContextObject, const FString Tag)
{
	UNBDebugSubsystem* DS = GetDebugSubsystem(WorldContextObject);
	DS->MakeDebugTagInactive(Tag);
}

void UNBDebugLibrary::NBPrintString(const UObject* WorldContextObject, const FString Tag, const FString& InString,
	const bool bPrintToScreen, const bool bPrintToLog, const FLinearColor TextColor, const float Duration, const FName Key)
{
	const UNBDebugSubsystem* DS = GetDebugSubsystem(WorldContextObject);
	// ReSharper disable once CppTooWideScopeInitStatement
	const bool IsTagActive = DS->IsDebugTagActive(Tag);

	if (!IsTagActive) return;

	UKismetSystemLibrary::PrintString(WorldContextObject, InString, bPrintToScreen, bPrintToLog, TextColor, Duration, Key);
}

void UNBDebugLibrary::NBPrint(const UObject* WorldContextObject, const FString Tag, const FString& InString, const FName Key)
{
	NBPrintString(WorldContextObject, Tag, InString, true, false, FColor::Yellow, InString.Len() * 0.2f, Key);
}