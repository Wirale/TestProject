// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingReceiverDataModel.h"
#include "BuildingSharedResourceDataModel.generated.h"

UCLASS()
class TESTPROJECT_API UBuildingSharedResourceDataModel : public UBuildingReceiverDataModel
{
	GENERATED_BODY()

protected:
	virtual void PostInitProperties() override;

protected:
	virtual void SetResource(int InResource) override;
	virtual void BeginPlay();

public:
	UFUNCTION()
	void OnChangeSharedResource(int NewSharedResource);	
};
