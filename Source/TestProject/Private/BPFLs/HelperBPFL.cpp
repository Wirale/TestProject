// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFLs/HelperBPFL.h"

#include "Kismet/GameplayStatics.h"
#include "Objects/BaseBuildingDataModel.h"
#include "Settings/BuildingSettings.h"
#include "SubSystem/BuildingsControlGameInstanceSubsystem.h"

void UHelperBPFL::SpawnBuildingByType(const UObject* WorldContextObject, EBuildingType BuildingType)
{
	UBuildingsControlGameInstanceSubsystem* BuildingsSubsystem = GetBuildingsControlGameInstanceSubsystem(WorldContextObject);
	if (IsValid(BuildingsSubsystem))
	{
		BuildingsSubsystem->SpawnNewBuild(BuildingType);
	}
}



void UHelperBPFL::OpenNewLevelByDirection(const UObject* WorldContextObject, ENewLevelDirection NewLevelDirection)
{
	const UWorld* World = WorldContextObject->GetWorld();
	if (IsValid(World))
	{
		const FName MapName = FName(World->GetName());
		const TArray<FName>& LevelNames =  UBuildingSettings::GetBuildingSettings()->LevelNames;
		int32 IndexMap = LevelNames.Find(MapName);
		if (IndexMap != INDEX_NONE)
		{
			if (NewLevelDirection == LEFT)
			{
				--IndexMap;
			}
			else
			{
				++IndexMap;
			}
			
			if (IndexMap >= LevelNames.Num())
			{
				UGameplayStatics::OpenLevel(WorldContextObject, LevelNames[0]);
			}
			else if (IndexMap < 0)
			{
				UGameplayStatics::OpenLevel(WorldContextObject, LevelNames[LevelNames.Num() - 1]);
			}
			else
			{
				UGameplayStatics::OpenLevel(WorldContextObject, LevelNames[IndexMap]);
			}
		}
		
	}
}

UBuildingsControlGameInstanceSubsystem* UHelperBPFL::GetBuildingsControlGameInstanceSubsystem(const UObject* WorldContextObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	if (IsValid(GameInstance))
	{
		return GameInstance->GetSubsystem<UBuildingsControlGameInstanceSubsystem>();
	}

	return nullptr;
}

USharedResourceManager* UHelperBPFL::GetSharedResourceManager(const UObject* WorldContextObject)
{
	const UBuildingsControlGameInstanceSubsystem* BuildingsControlGameInstanceSubsystem = GetBuildingsControlGameInstanceSubsystem(WorldContextObject);
	if(BuildingsControlGameInstanceSubsystem)
	{
		return BuildingsControlGameInstanceSubsystem->GetSharedResourceManager();
	}

	return nullptr;
}
