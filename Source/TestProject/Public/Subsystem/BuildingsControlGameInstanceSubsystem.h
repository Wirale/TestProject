// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Static/BuildingEnum.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BuildingsControlGameInstanceSubsystem.generated.h"

USTRUCT()
struct FBuildingDataModels
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<class UBaseBuildingDataModel*> BuildingDataModels;

	void AddNewBuilding(UBaseBuildingDataModel* BuildingDataModel)
	{
		BuildingDataModels.Add(BuildingDataModel);
	}
};

UCLASS()
class TESTPROJECT_API UBuildingsControlGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void SpawnNewBuild(EBuildingType BuildingType);
	class UBaseBuildingDataModel* GetNearestBuildingToPoint(const FVector& Point);
	class USharedResourceManager* GetSharedResourceManager() const;
	void SpawnBuildingsByLevelName(const FString& LevelName);

private:
	class UBaseBuildingDataModel* CreateDataModelByBuildingType(EBuildingType BuildingType);
	AActor* SpawnActor3DViewBuildingByForwardPlayer(FVector& SpawnLocation);
	AActor* SpawnActor3DViewBuildingByLocation(const FVector& SpawnLocation);
	void CreateSharedResourceManager();
	

protected:
	UPROPERTY()
	TMap<FString, FBuildingDataModels> BuildingInLevel;

	UPROPERTY()
	class USharedResourceManager* SharedResourceManager;
};
