// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/BuildingReceiverDataModel.h"

#include "BPFLs/HelperBPFL.h"
#include "Settings/BuildingSettings.h"
#include "SubSystem/BuildingsControlGameInstanceSubsystem.h"

UBuildingReceiverDataModel::UBuildingReceiverDataModel()
{
	CurrentResource = 0;
}

void UBuildingReceiverDataModel::SetSpawnLocation(const FVector& InLocation)
{
	Super::SetSpawnLocation(InLocation);

	SetupSourceBuilding();
}

void UBuildingReceiverDataModel::SetupSourceBuilding()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UBuildingsControlGameInstanceSubsystem* BuildingsSubsystem = UHelperBPFL::GetBuildingsControlGameInstanceSubsystem(World);
		if (IsValid(BuildingsSubsystem))
		{
			SourceBuilding = BuildingsSubsystem->GetNearestBuildingToPoint(GetSpawnLocation());
			World->GetTimerManager().SetTimer(SharingResourcesTimerHandle, this, &UBuildingReceiverDataModel::RetrieveResource, UBuildingSettings::GetBuildingSettings()->ResourceAddFrequency, true);
		}
	}
}

const FVector& UBuildingReceiverDataModel::GetSourceLocation() const
{
	if (SourceBuilding.IsValid())
	{
		return SourceBuilding->GetSpawnLocation();
	}

	return FVector::ZeroVector;
}

void UBuildingReceiverDataModel::RetrieveResource()
{
	if (SourceBuilding.IsValid())
	{
		const bool bIsSuccessIncrease = SourceBuilding->SubtractResources();
		if (bIsSuccessIncrease)
		{
			AddResources();
		}
	}
}
