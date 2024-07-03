// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystemGameInstance.h"

#include "BPFLs/HelperBPFL.h"
#include "SubSystem/BuildingsControlGameInstanceSubsystem.h"

void UBuildingSystemGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	if (IsValid(NewWorld))
	{
		UBuildingsControlGameInstanceSubsystem* BuildingsControlGameInstanceSubsystem = UHelperBPFL::GetBuildingsControlGameInstanceSubsystem(NewWorld);
		if (IsValid(BuildingsControlGameInstanceSubsystem))
		{
			BuildingsControlGameInstanceSubsystem->SpawnBuildingsByLevelName(NewWorld->GetName());
		}
	}
}
