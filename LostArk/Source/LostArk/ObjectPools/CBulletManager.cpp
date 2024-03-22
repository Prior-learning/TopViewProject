#include "CBulletManager.h"
#include "../Global.h"
#include "../Combat/CBullet.h"

ACBulletManager *ACBulletManager::mInstance = nullptr;


ACBulletManager::ACBulletManager()
{

}
void ACBulletManager::Init()
{
    for (int i = 0; i < mBulletPoolSize; i++)
    {
        BulletPool.Enqueue(GetWorld()->SpawnActor<ACBullet>(bulletClass, FVector::ZeroVector, FRotator::ZeroRotator));
        Poolsize++;
        CLog::Log("BulletInit");

    }
}

void ACBulletManager::Expand()
{
    for (int i = 0; i < mExpandSize; i++)
    {
        BulletPool.Enqueue(GetWorld()->SpawnActor<ACBullet>(bulletClass, FVector::ZeroVector, FRotator::ZeroRotator));
        Poolsize++;
        CLog::Log("BulletExpand");
        
    }
}

void ACBulletManager::Return(ACBullet *target)
{
    BulletPool.Enqueue(target);
    Poolsize++;
    CLog::Log("BulletReturn");
    UE_LOG(LogTemp, Warning, TEXT("PoolSize:%d "), GetPoolsize());
}

ACBullet *ACBulletManager::Pop()
{
    ACBullet *PopBullet;
    if (!BulletPool.IsEmpty())
    {

        BulletPool.Dequeue(PopBullet);
        Poolsize--;

        CLog::Log("BulletPop");
        UE_LOG(LogTemp, Warning, TEXT("PoolSize:%d "), GetPoolsize()); 

        return PopBullet;
    }
    else
    {
        Expand();
        BulletPool.Dequeue(PopBullet);
        Poolsize--;
        return PopBullet;
    }
}

ACBulletManager &ACBulletManager::GetInstance()
{
    return *mInstance;
}

void ACBulletManager::BeginPlay()
{
    Super::BeginPlay();
    mInstance = this;
    Init();
}
