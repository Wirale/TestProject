#include "SubSystem\BuildingsControlGameInstanceSubsystem.h"

#include "Interfaces/Initialize3DViewInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/BaseBuildingDataModel.h"
#include "Objects/Managers/SharedResourceManager.h"
#include "Settings/BuildingSettings.h"

constexpr float DistanceToSpawnActor = 50.f;

void UBuildingsControlGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	CreateSharedResourceManager();
}

void UBuildingsControlGameInstanceSubsystem::SpawnNewBuild(EBuildingType BuildingType)
{
	UBaseBuildingDataModel* BuildingDataModel = CreateDataModelByBuildingType(BuildingType);
	if (!IsValid(BuildingDataModel))
	{
		return;
	}
	
	FVector SpawnLocation = FVector::ZeroVector;
	IInitialize3DViewInterface* Initialize3DViewInterface = Cast<IInitialize3DViewInterface>(SpawnActor3DViewBuildingByForwardPlayer(SpawnLocation));
	if (Initialize3DViewInterface)
	{
		BuildingDataModel->SetSpawnLocation(SpawnLocation);
		
		Initialize3DViewInterface->InitializeWithDataModel(BuildingDataModel, BuildingDataModel->GetResource());			

		const UWorld* World = GetWorld();
		if (IsValid(World))
		{
			FBuildingDataModels& BuildingDataModelsSet = BuildingInLevel.FindOrAdd(World->GetName());
			BuildingDataModelsSet.AddNewBuilding(BuildingDataModel);
		}
	}
	
}

UBaseBuildingDataModel* UBuildingsControlGameInstanceSubsystem::CreateDataModelByBuildingType(EBuildingType BuildingType)
{
	const auto& BuildingClasses = UBuildingSettings::GetBuildingSettings()->BuildingClasses;

	const UClass* BuildClass = BuildingClasses.FindRef(BuildingType).LoadSynchronous();
	if (!IsValid(BuildClass))
	{
		return nullptr;
	}
	
	return NewObject<UBaseBuildingDataModel>(this, BuildClass);
}

AActor* UBuildingsControlGameInstanceSubsystem::SpawnActor3DViewBuildingByForwardPlayer(FVector& SpawnLocation)
{
	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return nullptr;
	}
	
	const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(World, 0);
	if (IsValid(PlayerCameraManager))
	{
		const FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		const FVector ForwardCamera = PlayerCameraManager->GetCameraRotation().Vector();
		SpawnLocation = CameraLocation + ForwardCamera * DistanceToSpawnActor;
		return SpawnActor3DViewBuildingByLocation(SpawnLocation);
	}
	
	return nullptr;
}

AActor* UBuildingsControlGameInstanceSubsystem::SpawnActor3DViewBuildingByLocation(const FVector& SpawnLocation)
{
	UWorld* World = GetWorld();
	
	if (IsValid(World) && !SpawnLocation.IsZero())
	{
		UClass* Building3DViewClass = UBuildingSettings::GetBuildingSettings()->Building3DViewClass.LoadSynchronous();
		if (IsValid(Building3DViewClass))
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			AActor* SpawnedActor = World->SpawnActor<AActor>(Building3DViewClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
			if (IsValid(SpawnedActor))
			{
				return SpawnedActor;
			}
		}
	}

	return nullptr;
}

void UBuildingsControlGameInstanceSubsystem::CreateSharedResourceManager()
{
	SharedResourceManager = NewObject<USharedResourceManager>();
}

UBaseBuildingDataModel* UBuildingsControlGameInstanceSubsystem::GetNearestBuildingToPoint(const FVector& Point)
{
	const UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return nullptr;
	}

	const FBuildingDataModels* BuildingDataModelsSet = BuildingInLevel.Find(World->GetName());
	if (BuildingDataModelsSet)
	{
		TArray<UBaseBuildingDataModel*> DataModels = BuildingDataModelsSet->BuildingDataModels;
	
		if (DataModels.Num() <= 0)
		{
			return nullptr;
		}
	
		UBaseBuildingDataModel* CurrentBuildingDataModel = DataModels[0];
		float MinDistanceToPoint = FVector::Distance(CurrentBuildingDataModel->GetSpawnLocation(), Point);

		for (int32 It = 1; It < DataModels.Num(); ++It)
		{
			FVector CurrentPoint = DataModels[It]->GetSpawnLocation();

			const float DistanceBetweenPoints = FVector::Distance(CurrentPoint, Point);

			if (DistanceBetweenPoints < MinDistanceToPoint)
			{
				MinDistanceToPoint = DistanceBetweenPoints;
				CurrentBuildingDataModel = DataModels[It];
			}
		}

		return CurrentBuildingDataModel;
	}

	return nullptr;
}


USharedResourceManager* UBuildingsControlGameInstanceSubsystem::GetSharedResourceManager() const
{
	return SharedResourceManager;
}

void UBuildingsControlGameInstanceSubsystem::SpawnBuildingsByLevelName(const FString& LevelName)
{
	const FBuildingDataModels* BuildingDataModels = BuildingInLevel.Find(LevelName);
	if (BuildingDataModels)
	{
		TArray<class UBaseBuildingDataModel*> DataModels = BuildingDataModels->BuildingDataModels;
		for(const auto& DataModel : DataModels)
		{
			IInitialize3DViewInterface* Initialize3DViewInterface = Cast<IInitialize3DViewInterface>(SpawnActor3DViewBuildingByLocation(DataModel->GetSpawnLocation()));
			if (Initialize3DViewInterface)
			{
				Initialize3DViewInterface->InitializeWithDataModel(DataModel, DataModel->GetResource());
			}
		}
	}
}
