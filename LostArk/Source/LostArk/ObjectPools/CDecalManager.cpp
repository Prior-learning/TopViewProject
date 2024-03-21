#include "CDecalManager.h"
#include "CDecalObject.h"

ACDecalManager *ACDecalManager::Instance = nullptr;
TQueue<class ACDecalObject *> ACDecalManager::mObjectpool;

ACDecalManager::ACDecalManager()
{
    Instance = this;
}
ACDecalManager::~ACDecalManager()
{
    mObjectpool.Empty();
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
// Tail �� �� �����µ�. static ���� ������ �ϴϱ� Tail�� Pop()���� ���� �Ҵ������� �� ��.

void ACDecalManager::SetDecalInfo(const EDecalShape &shape, const FRotator &direction, const float degree,
                                  const FVector &location, const float circum, const float distancefromtcenter
                                  )
{
    if (Instance == nullptr)
        return;
    if (mObjectpool.IsEmpty())
    {   
        return;
    }
    ensureMsgf(!mObjectpool.IsEmpty(), TEXT("mObjectpool is Empty"));

    ACDecalObject *data;
    mObjectpool.Dequeue(data);
    mObjectpool.Enqueue(data);

    data->SetDecalInfo(shape, direction, degree, location, circum, distancefromtcenter);
}




