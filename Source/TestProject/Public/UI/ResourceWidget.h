#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/UpdateResourceInterface.h"
#include "ResourceWidget.generated.h"

UCLASS()
class TESTPROJECT_API UResourceWidget : public UUserWidget, public IUpdateResourceInterface
{
	GENERATED_BODY()

public:
	virtual void UpdateResource(int NewResource) override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResourceTextBlock;
};
