// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/BuildingSharedResourceDataModel.h"

#include "BPFLs/HelperBPFL.h"
#include "Objects/Managers/SharedResourceManager.h"


void UBuildingSharedResourceDataModel::SetResource(int InResource)
{	
	USharedResourceManager* SharedResourceManager = UHelperBPFL::GetSharedResourceManager(GetWorld());
	if (!IsValid(SharedResourceManager))
	{
		return;
	}

	SharedResourceManager->SetSharedResource(InResource);
}

void UBuildingSharedResourceDataModel::PostInitProperties()
{
	Super::PostInitProperties();
	
	if (GetOuter() && GetOuter()->GetWorld())
	{
		BeginPlay();
	}
}

void UBuildingSharedResourceDataModel::BeginPlay()
{
	USharedResourceManager* SharedResourceManager = UHelperBPFL::GetSharedResourceManager(GetWorld());
	if (!IsValid(SharedResourceManager))
	{
		return;
	}

	SharedResourceManager->OnChangeSharedResource.AddUObject(this, &UBuildingSharedResourceDataModel::OnChangeSharedResource);
}

void UBuildingSharedResourceDataModel::OnChangeSharedResource(int NewSharedResource)
{
	CurrentResource = NewSharedResource;
	if (OnChangeResource.IsBound())
	{
		OnChangeResource.Execute(CurrentResource);
	}
}
