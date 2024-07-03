#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UpdateResourceInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UUpdateResourceInterface : public UInterface
{
	GENERATED_BODY()
};

class IUpdateResourceInterface
{    
	GENERATED_BODY()

public:
	virtual void UpdateResource(int NewResource) = 0;
};
