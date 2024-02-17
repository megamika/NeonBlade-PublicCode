// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppUEBlueprintCallableFunctionUnused
#pragma once

#include "CoreMinimal.h"
#include "NBFunctionLibrary.h"
#include "Debug/NBDebugSubsystem.h"
#include "NBDebugLibrary.generated.h"



UCLASS()
class NEONBLADE_API UNBDebugLibrary : public UNBFunctionLibrary
{
	GENERATED_BODY()
	
	public:

	static bool IsDebugTagActive(const UObject* WorldContextObject, const FString& Tag);

	static UNBDebugSubsystem* GetDebugSubsystem(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, DevelopmentOnly))
	static void ActivateDebugTag(const UObject* WorldContextObject, const FString Tag);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, DevelopmentOnly))
	static void DeactivateDebugTag(const UObject* WorldContextObject, const FString Tag);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category="Development")
	static void NBPrintString(const UObject* WorldContextObject, const FString Tag, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0, 0.66, 1.0), float Duration = 2.f, const FName Key = NAME_None);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category="Development")
	static void NBPrint(const UObject* WorldContextObject, const FString Tag, const FString& InString = FString(TEXT("Hello")), const FName Key = NAME_None);

};
