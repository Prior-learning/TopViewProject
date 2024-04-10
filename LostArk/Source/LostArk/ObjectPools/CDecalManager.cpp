#include "CDecalManager.h"
#include "CDecalObject.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

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



void ACDecalManager::SetDecalInfo(FDecalInfo &info)
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

    data->SetDecalInfo(info);
   
}
void ACDecalManager::SetDecalInfo_LocationToPlayer(FDecalInfo &info)
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

     ACharacter *player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!!player)
    {
        info.location = player->GetActorLocation();
        info.location.Z = -250.f;
    }
    else
    {
        FString str = "controller Cast Fail";
        UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
    }

    
    data->SetDecalInfo(info);
}





