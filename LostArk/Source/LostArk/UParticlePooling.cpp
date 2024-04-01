#include "UParticlePooling.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/BoxComponent.h"
#include "Combat/ICombat.h"

#include "Global.h"
AUParticlePooling::AUParticlePooling() 
{
	PrimaryActorTick.bCanEverTick = true;
    mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
    RootComponent = mParticle;
    mBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    mBoxCollider->AttachToComponent(mParticle,FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
    mBoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel11);
}

AUParticlePooling::~AUParticlePooling()
{
}

void AUParticlePooling::BeginPlay()
{
	Super::BeginPlay();

    mBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AUParticlePooling::OnComponentBeginOverlap);
    mBoxCollider->SetGenerateOverlapEvents(false);
}
void AUParticlePooling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUParticlePooling::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                                UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult &SweepResult)
{
    //CLog::Print(OtherComp->GetOwner()->GetName());

    IICombat *combat = Cast<IICombat>(OtherComp->GetOwner());
    ensureMsgf(combat != nullptr, TEXT("Icombat Cast Fail"));
    
    FDamageEvent type;
    combat->Damaged(-mPower, type, nullptr, this, GetActorLocation(), nullptr);
}

void AUParticlePooling::SetParticle(UParticleSystem *InParticle)
{

    mParticle->SetTemplate(InParticle);
    mParticle->Activate(true);
    mBoxCollider->SetGenerateOverlapEvents(true);

    GetWorldTimerManager().SetTimer(ReturnHandle, this, &AUParticlePooling::OffBoxOverlap, 0.2f, false);
}

void AUParticlePooling::OffBoxOverlap()
{
    mBoxCollider->SetGenerateOverlapEvents(false);
    mPower = 0.f;
}
