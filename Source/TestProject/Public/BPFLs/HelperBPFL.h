// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Static/BuildingEnum.h"
#include "HelperBPFL.generated.h"

UCLASS(meta=(BlueprintThreadSafe))
class TESTPROJECT_API UHelperBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void SpawnBuildingByType(const UObject* WorldContextObject, EBuildingType BuildingType);
	static void OpenNewLevelByDirection(const UObject* WorldContextObject, ENewLevelDirection NewLevelDirection);
	static class UBuildingsControlGameInstanceSubsystem* GetBuildingsControlGameInstanceSubsystem(const UObject* WorldContextObject);
	static class USharedResourceManager* GetSharedResourceManager(const UObject* WorldContextObject);
};
