// Fill out your copyright notice in the Description page of Project Settings.

#include "Building3DView.h"

#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/ReceiverInfoInterface.h"
#include "Interfaces/UpdateResourceInterface.h"
#include "Objects/BaseBuildingDataModel.h"


ABuilding3DView::ABuilding3DView()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(StaticMesh);

	ResourceWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ResourceWidget"));
	ResourceWidget->SetupAttachment(GetRootComponent());

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(GetRootComponent());
}

void ABuilding3DView::BeginDestroy()
{
	if (DataModel.IsValid())
	{
		DataModel->OnChangeResource.Unbind();
	}
	
	Super::BeginDestroy();
}

void ABuilding3DView::InitializeWithDataModel(UBaseBuildingDataModel* BaseBuildingDataModel, int32 InResource)
{
	if(IsValid(BaseBuildingDataModel))
	{
		DataModel = BaseBuildingDataModel;
		DataModel->OnChangeResource.BindUObject(this, &ABuilding3DView::OnChangeResource);
		OnChangeResource(InResource);
		const IReceiverInfoInterface* ReceiverInfoInterface = Cast<IReceiverInfoInterface>(BaseBuildingDataModel);
		if (ReceiverInfoInterface)
		{
			SetupDirectionArrow(ReceiverInfoInterface->GetSourceLocation());
		}
		else
		{
			ArrowComponent->DestroyComponent();
		}
		
	}
}

void ABuilding3DView::OnChangeResource(int InResource)
{
	if (IsValid(ResourceWidget))
	{
		IUpdateResourceInterface* UpdateResourceInterface = Cast<IUpdateResourceInterface>(ResourceWidget->GetWidget());
		if (UpdateResourceInterface)
		{
			UpdateResourceInterface->UpdateResource(InResource);
		}
	}
}

void ABuilding3DView::SetupDirectionArrow(const FVector& SourceLocation)
{
	if(IsValid(ArrowComponent))
	{
		const FVector& ArrowLocation = ArrowComponent->GetComponentLocation();
		ArrowComponent->SetWorldRotation((SourceLocation - ArrowLocation).Rotation());
	}
}
