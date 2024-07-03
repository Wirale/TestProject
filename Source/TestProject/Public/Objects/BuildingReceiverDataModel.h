// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingDataModel.h"
#include "Interfaces/ReceiverInfoInterface.h"
#include "BuildingReceiverDataModel.generated.h"

UCLASS()
class TESTPROJECT_API UBuildingReceiverDataModel : public UBaseBuildingDataModel, public IReceiverInfoInterface 
{
	GENERATED_BODY()

public:
	UBuildingReceiverDataModel();

public:
	virtual void SetSpawnLocation(const FVector& InLocation) override;

protected:
	virtual const FVector& GetSourceLocation() const override;

protected:
	void RetrieveResource();
	void SetupSourceBuilding();

private:
	TWeakObjectPtr<UBaseBuildingDataModel> SourceBuilding;
	FTimerHandle SharingResourcesTimerHandle;
};
