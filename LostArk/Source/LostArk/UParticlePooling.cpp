#include "UParticlePooling.h"
#include "Particles/ParticleSystemComponent.h"

AUParticlePooling::AUParticlePooling() 
{
	
    mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
    RootComponent = mParticle;
}

AUParticlePooling::~AUParticlePooling()
{
}

void AUParticlePooling::BeginPlay()
{
    Super::BeginPlay();
}



void AUParticlePooling::SetParticle(UParticleSystem *InParticle)
{

    mParticle->SetTemplate(InParticle);
    mParticle->Activate(true);

}

