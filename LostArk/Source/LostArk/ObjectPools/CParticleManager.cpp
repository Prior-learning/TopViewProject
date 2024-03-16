#include "CParticleManager.h"
#include "../UParticlePooling.h"
#include "../Global.h"

#define POOLSIZE 10

ACParticleManager *ACParticleManager::instance = nullptr;

ACParticleManager::ACParticleManager()
{
	PrimaryActorTick.bCanEverTick = true;

}
ACParticleManager::~ACParticleManager()
{
    CLog::Log("Destructor Called");
    /*for (int i = 0; i < POOLSIZE; i++)
        delete particlePool[i];*/
}

void ACParticleManager::BeginPlay()
{
	Super::BeginPlay();
    instance = this;

    particlePool.SetNum(POOLSIZE);
    for (int i = 0; i < POOLSIZE; i++)
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
    idx %= POOLSIZE;

    return particlePool[idx];
}

