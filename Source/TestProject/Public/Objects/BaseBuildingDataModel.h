// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseBuildingDataModel.generated.h"

DECLARE_DELEGATE_OneParam(FOnChangeResource, int);

UCLASS()
class TESTPROJECT_API UBaseBuildingDataModel : public UObject
{
	GENERATED_BODY()

public:
	UBaseBuildingDataModel();

public:
	bool SubtractResources();
	void AddResources();
	int GetResource() const;
	
	const FVector& GetSpawnLocation() const;
	virtual void SetSpawnLocation(const FVector& InLocation);

protected:
	virtual void SetResource(int InResource);

public:
	FOnChangeResource OnChangeResource;

protected:
	int CurrentResource;
	FVector SpawnLocation;
};
