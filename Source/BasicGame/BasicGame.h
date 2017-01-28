// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

UENUM(BlueprintType)
enum class EStancilColor : uint8
{
	SC_Green = 250 UMETA(DispleyName = "Green"),
	SC_Blue = 251 UMETA(DispleyName = "Blue"),
	SC_Red = 252 UMETA(DispleyName = "Red"),
	SC_White = 253 UMETA(DispleyName = "White")
};