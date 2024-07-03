#include "Objects/Managers/SharedResourceManager.h"

USharedResourceManager::USharedResourceManager()
{
	SharedResource = 0;
}

int USharedResourceManager::GetSharedResource() const
{
	return SharedResource;
}

void USharedResourceManager::SetSharedResource(int InSharedResource)
{
	SharedResource = InSharedResource;
	if (OnChangeSharedResource.IsBound())
	{
		OnChangeSharedResource.Broadcast(SharedResource);
	}
}
