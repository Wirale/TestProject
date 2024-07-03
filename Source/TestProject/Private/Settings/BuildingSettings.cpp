#include "Settings/BuildingSettings.h"

UBuildingSettings::UBuildingSettings()
{
	ResourcePerTime = 1;
	ResourceAddFrequency = 1.f;
	BuildingClasses = {};
	Building3DViewClass = nullptr;
	LevelNames = {};
}

UBuildingSettings* UBuildingSettings::GetBuildingSettings()
{
	return GetMutableDefault<UBuildingSettings>();
}
