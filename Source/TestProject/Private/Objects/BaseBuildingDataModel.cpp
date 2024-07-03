// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/BaseBuildingDataModel.h"

#include "Settings/BuildingSettings.h"

UBaseBuildingDataModel::UBaseBuildingDataModel()
{
	CurrentResource = 100;
	SpawnLocation = FVector::ZeroVector;
}

bool UBaseBuildingDataModel::SubtractResources()
{
	const int NewResource = CurrentResource - UBuildingSettings::GetBuildingSettings()->ResourcePerTime;
	if (NewResource >= 0)
	{
		SetResource(NewResource);
		return true;
	}
	
	return false;
}

void UBaseBuildingDataModel::AddResources()
{
	const int NewResource = CurrentResource + UBuildingSettings::GetBuildingSettings()->ResourcePerTime;
	SetResource(NewResource);
}

int UBaseBuildingDataModel::GetResource() const
{
	return CurrentResource;
}

void UBaseBuildingDataModel::SetResource(int InResource)
{
	CurrentResource = InResource;
	
	if (OnChangeResource.IsBound())
	{
		OnChangeResource.Execute(CurrentResource);
	}
}

const FVector& UBaseBuildingDataModel::GetSpawnLocation() const
{
	return SpawnLocation;
}

void UBaseBuildingDataModel::SetSpawnLocation(const FVector& InLocation)
{
	SpawnLocation = InLocation;
}
