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
        CLog::Log("BulletEnqueue");

    }
}

void ACBulletManager::Expand()
{
    for (int i = 0; i < mExpandSize; i++)
    {
        BulletPool.Enqueue(GetWorld()->SpawnActor<ACBullet>(bulletClass, FVector::ZeroVector, FRotator::ZeroRotator));
    }
}

void ACBulletManager::Return(ACBullet *target)
{
    BulletPool.Enqueue(target);
}

ACBullet *ACBulletManager::Pop()
{
    ACBullet *PopBullet;
    if (!BulletPool.IsEmpty())
    {

        BulletPool.Dequeue(PopBullet);
        return PopBullet;
    }
    else
    {
        Expand();
        BulletPool.Dequeue(PopBullet);
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
