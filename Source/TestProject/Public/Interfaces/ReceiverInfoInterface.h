// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ReceiverInfoInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UReceiverInfoInterface : public UInterface
{
	GENERATED_BODY()
};

class IReceiverInfoInterface
{    
	GENERATED_BODY()

public:
	virtual const FVector& GetSourceLocation() const = 0;
};
