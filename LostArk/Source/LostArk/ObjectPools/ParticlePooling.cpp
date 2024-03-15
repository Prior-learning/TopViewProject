#include "ParticlePooling.h"
#include "../UParticlePooling.h"
#include "../Global.h"

UParticlePooling::UParticlePooling()
{
    particlePool.Emplace(GetWorld()->SpawnActor<AUParticlePooling>());
}

UParticlePooling::~UParticlePooling()
{
    CLog::Log("Called Destructor");
}

UParticlePooling &UParticlePooling::Get()
{
    UParticlePooling *instance = CastChecked<UParticlePooling>(GEngine->GameSingleton);
    if (instance)
        return *instance;

    CLog::Log("Singleton Invalid");
    return *NewObject<UParticlePooling>();
}

AUParticlePooling* UParticlePooling::GetParticle()
{
    static int idx = -1;
    idx++;
    idx %= particlePool.Num();
    
    return particlePool[idx];
}

//TArray<AUParticlePooling *> UParticlePooling::particlePool;
//
//UParticlePooling::~UParticlePooling()
//{
//    CLog::Log("UObjectPooling Destructor Called");
//}
//
//void UParticlePooling::Create(UWorld *InWorld, int poolsize)
//{
//    if (particlePool.Num() != 0)
//        return;
//    static UParticlePooling instance;
//
//    for (int i = 0; i < poolsize; i++)
//    {
//        AUParticlePooling *temp = InWorld->SpawnActor<AUParticlePooling>();
//        particlePool.Emplace(std::move(temp));
//    }
//
//    CLog::Log("ObejectPooling  Create Called");
//}
//
//AUParticlePooling *UParticlePooling::GetParticle()
//{
//
//    static int idx = -1;
//    idx++;
//    idx %= particlePool.Num();
//
//    return particlePool[idx];
//}
