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
        ACBullet *bullet = GetWorld()->SpawnActor<ACBullet>(bulletClass, FVector(0,0,2500), FRotator::ZeroRotator);
        BulletPool.Enqueue(bullet);
        Poolsize++;
        //CLog::Log("BulletInit");

    }
}

void ACBulletManager::Expand()
{
    for (int i = 0; i < mExpandSize; i++)
    {
        ACBullet *bullet = GetWorld()->SpawnActor<ACBullet>(bulletClass, FVector(0, 0, 2500), FRotator::ZeroRotator);
        BulletPool.Enqueue(bullet);
        Poolsize++;
        //CLog::Log("BulletExpand");
        
    }
}

void ACBulletManager::Return(ACBullet *target)
{
    BulletPool.Enqueue(target);
    Poolsize++;
    //CLog::Log("BulletReturn");
    //UE_LOG(LogTemp, Warning, TEXT("PoolSize:%d "), GetPoolsize());
}

ACBullet *ACBulletManager::Pop()
{
    ACBullet *PopBullet;
    if (!BulletPool.IsEmpty())
    {
        BulletPool.Dequeue(PopBullet);
        Poolsize--;
        //CLog::Log("BulletPop");
        //UE_LOG(LogTemp, Warning, TEXT("PoolSize:%d "), GetPoolsize()); 

        return PopBullet;
    }
   
    Expand();
    BulletPool.Dequeue(PopBullet);
    Poolsize--;
    return PopBullet;
    
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
