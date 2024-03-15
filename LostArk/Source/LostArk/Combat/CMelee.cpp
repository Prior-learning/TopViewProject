#include "CMelee.h"
#include "../Global.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

#include "../Global.h"
#include "../Combat/ICombat.h"

using namespace std;



ACMelee::ACMelee()
{
    CHelpers::CreateComponent<USkeletalMeshComponent>(this, &mesh, "SkeletalMesh");
    CHelpers::CreateComponent<UBoxComponent>(this, &mCollider, "Collider", mesh);

    RootComponent = mesh;
}

void ACMelee::BeginPlay()
{
    Super::BeginPlay();
    OverlapActors.Reserve(6); // ´ë·« 6

    mCollider->OnComponentBeginOverlap.AddDynamic(this, &ACMelee::OnComponentBeginOverlap);
    mCollider->OnComponentEndOverlap.AddDynamic(this, &ACMelee::OnComponentEndOverlap);

    OffCollision();
}


void ACMelee::OnCollision()
{
    mCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACMelee::OffCollision()
{
    mCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACMelee::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult &SweepResult)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());

    IICombat *hitedActor = Cast<IICombat>(OtherComp->GetOwner());
    CheckNull(hitedActor);

    FDamageEvent mDamageEvent;
    
    hitedActor->Damaged(mPower, mDamageEvent, mController, this, OverlappedComponent->GetComponentLocation()
                        , mParticle);
}

void ACMelee::OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());
}

