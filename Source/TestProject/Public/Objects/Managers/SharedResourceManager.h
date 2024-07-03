// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SharedResourceManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeSharedResource, int /* NewSharedResource*/);

UCLASS()
class TESTPROJECT_API USharedResourceManager : public UObject
{
	GENERATED_BODY()

public:
	USharedResourceManager();
	
public:
	int GetSharedResource() const;
	void SetSharedResource(int InSharedResource);

public:
	FOnChangeSharedResource OnChangeSharedResource;

private:
	int SharedResource;
};
