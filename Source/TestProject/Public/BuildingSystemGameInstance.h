// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BuildingSystemGameInstance.generated.h"

UCLASS()
class TESTPROJECT_API UBuildingSystemGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
};
