#include "CDecalManager.h"
#include "CDecalObject.h"

ACDecalManager *ACDecalManager::Instance = nullptr;


ACDecalManager::ACDecalManager()
{
    Instance = this;
}

void ACDecalManager::BeginPlay()
{
    Super::BeginPlay();

    for (int i = 0; i < mPoolSize; i++)
        mObjectpool.Enqueue(GetWorld()->SpawnActor<ACDecalObject>(classof));
}

ACDecalManager *ACDecalManager::Get()
{
    return Instance;
}

void ACDecalManager::SetDecalInfo(EDecalShape& shape, FVector& location,float circum,float distancefromtcenter, float timer)
{
    if (this == nullptr)
        return;
    if (mObjectpool.IsEmpty())
        return;
    ACDecalObject *data;
    mObjectpool.Dequeue(data);
    mObjectpool.Enqueue(data);

    data->SetDecalInfo(shape, location, circum, distancefromtcenter, timer);
    
}




