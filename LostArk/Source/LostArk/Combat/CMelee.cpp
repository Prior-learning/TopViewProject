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


ACMelee *ACMelee::CreateWeapon(UWorld *world, TSubclassOf<class ACWeapon> classof , ACharacter *owner)
{
    FActorSpawnParameters params;
    params.Owner = owner;
   
    ACMelee *temp = world->SpawnActor<ACMelee>(classof, params);
    temp->AttachToComponent(owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),temp->mAttachBone);

    temp->mController = owner->GetController();

    return temp;
}

void ACMelee::BeginPlay()
{

    OverlapActors.Reserve(6); // ´ë·« 6

    mCollider->OnComponentBeginOverlap.AddDynamic(this, &ACMelee::OnComponentBeginOverlap);
    mCollider->OnComponentEndOverlap.AddDynamic(this, &ACMelee::OnComponentEndOverlap);

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

    ACharacter *hitedActor = Cast<ACharacter>(OtherComp->GetOwner());
    CheckNull(hitedActor);
    
    OverlapActors.AddUnique(hitedActor);
}

void ACMelee::OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    CheckTrue(OtherComp->GetOwner() == this->GetOwner());
    ACharacter *hitedActor = Cast<ACharacter>(OtherComp->GetOwner());
    CheckNull(hitedActor);

    int idx = -2; 
    if (OverlapActors.Find(hitedActor, idx))
    {
        OverlapActors.RemoveAt(idx);
        FDamageEvent mDamageEvent;
        CLog::Log(OverlappedComponent->GetFName().ToString());
        CLog::Log(OtherComp->GetFName().ToString());
        hitedActor->TakeDamage(mPower, mDamageEvent, mController, this);
        
    }
}

