#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Initialize3DViewInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInitialize3DViewInterface : public UInterface
{
	GENERATED_BODY()
};

class IInitialize3DViewInterface
{    
	GENERATED_BODY()

public:
	virtual void InitializeWithDataModel(class UBaseBuildingDataModel* BaseBuildingDataModel, int32 InResource) = 0;
};