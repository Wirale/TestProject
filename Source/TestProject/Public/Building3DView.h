// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Initialize3DViewInterface.h"
#include "Building3DView.generated.h"

UCLASS()
class TESTPROJECT_API ABuilding3DView : public AActor, public IInitialize3DViewInterface
{
	GENERATED_BODY()
	
public:	
	ABuilding3DView();

public:
	virtual void BeginDestroy() override;

public:
	virtual void InitializeWithDataModel(class UBaseBuildingDataModel* BaseBuildingDataModel, int32 InResource) override;

protected:
	UFUNCTION()
	void OnChangeResource(int InResource);

private:
	void SetupDirectionArrow(const FVector& SourceLocation);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UWidgetComponent* ResourceWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UArrowComponent* ArrowComponent;

private:
	TWeakObjectPtr<class UBaseBuildingDataModel> DataModel;
};
