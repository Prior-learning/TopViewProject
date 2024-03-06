#include "CMelee.h"
#include "../Global.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

#include "../Global.h"
using namespace std;


ACMelee::ACMelee()
{
    CHelpers::CreateComponent<UStaticMeshComponent>(this, &mesh, "SkeletalMesh");
    CHelpers::CreateComponent<UBoxComponent>(this, &mCollider, "Collider", mesh);

    RootComponent = mesh;
}


ACMelee *ACMelee::CreateWeapon(UWorld *world, TSubclassOf<class ACWeapon> classof , ACharacter *owner)
{
    FActorSpawnParameters params;
    params.Owner = owner;
   
    ACMelee *temp = world->SpawnActor<ACMelee>(classof, params);
    temp->AttachToComponent(owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),temp->mAttachBone);
    return temp;
}

//void ACMelee::BeginPlay()
//{
// /*   component->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
//    component->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);*/
//}

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
    CLog::Log("Overlap Begin");
}

void ACMelee::OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    CLog::Log("Overlap End");
}

