#include "UParticlePooling.h"
#include "Particles/ParticleSystemComponent.h"
#include "Global.h"
#include <memory>

#define POOLSIZE 10

AUParticlePooling::AUParticlePooling() 
	: particle(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
    CHelpers::CreateComponent<UParticleSystemComponent>(this, &particle, "ParicleComp");
    RootComponent = particle;
}

AUParticlePooling::~AUParticlePooling()
{
}

void AUParticlePooling::BeginPlay()
{
	Super::BeginPlay();
    
}
void AUParticlePooling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUParticlePooling::SetParticle(UParticleSystem *InParticle)
{
    particle->Template = InParticle;
    particle->Activate(true);
 
}
