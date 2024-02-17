// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug/NBDebugSubsystem.h"


bool UNBDebugSubsystem::IsDebugTagActive(const FString& Tag) const
{
	return ActiveDebugTags.Contains(Tag);
}

void UNBDebugSubsystem::MakeDebugTagActive(const FString& Tag)
{
	ActiveDebugTags.Add(Tag);
}

void UNBDebugSubsystem::MakeDebugTagInactive(const FString& Tag)
{
	ActiveDebugTags.Remove(Tag);
}


