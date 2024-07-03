#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Static/BuildingEnum.h"
#include "BuildingSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName="Building Settings"))
class TESTPROJECT_API UBuildingSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBuildingSettings();

public:
	static UBuildingSettings* GetBuildingSettings();
	
	UPROPERTY(config, EditAnywhere, Category = "Change resource")
	int ResourcePerTime;
	
	UPROPERTY(config, EditAnywhere, Category = "Change resource")
	float ResourceAddFrequency;

	UPROPERTY(config, EditAnywhere, Category = "Classes of building")
	TMap<TEnumAsByte<EBuildingType>, TSoftClassPtr<class UBaseBuildingDataModel>> BuildingClasses;

	UPROPERTY(config, EditAnywhere, Category = "Classes of building in 3D")
	TSoftClassPtr<AActor> Building3DViewClass;

	UPROPERTY(config, EditAnywhere, Category = "Level")
	TArray<FName> LevelNames;
};
