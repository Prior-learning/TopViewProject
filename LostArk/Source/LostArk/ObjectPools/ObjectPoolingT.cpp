#include "ObjectPoolingT.h"
#include "../Combat/CBullet.h"

AObjectPoolingT::AObjectPoolingT()
{

}

void AObjectPoolingT::Init()
{
    for (int i = 0; i < mBulletPoolSize; i++)
    {
        BulletPool.Enqueue(GetWorld()->SpawnActor<ACBullet>(bulletClass, FVector::ZeroVector, FRotator::ZeroRotator));
    }
}

void AObjectPoolingT::Return(ACBullet* target)
{
    BulletPool.Enqueue(target);
}

ACBullet *AObjectPoolingT::Pop()
{
    ACBullet *PopBullet;

    BulletPool.Dequeue(PopBullet);
    return PopBullet;
}

void AObjectPoolingT::BeginPlay()
{
	Super::BeginPlay();
	
}
