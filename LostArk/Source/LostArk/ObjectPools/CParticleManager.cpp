#include "CParticleManager.h"
#include "../UParticlePooling.h"
#include "../Global.h"

ACParticleManager *ACParticleManager::instance = nullptr;

ACParticleManager::ACParticleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}
ACParticleManager::~ACParticleManager()
{
    CLog::Log("Destructor Called");
}

void ACParticleManager::BeginPlay()
{
	Super::BeginPlay();
    instance = this;

    particlePool.SetNum(mPoolSize);
    for (int i = 0; i < mPoolSize; i++)
    {
        particlePool[i] = GetWorld()->SpawnActor<AUParticlePooling>(classOfObject);
    }
}

void ACParticleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACParticleManager& ACParticleManager::Get()
{
    return *instance;
}

AUParticlePooling *ACParticleManager::GetParticle()
{
    static int idx = -1;
    idx++;
    idx %= mPoolSize;

    return particlePool[idx];
}

