#include "CGun.h"
#include "../Global.h"
#include "GameFramework/Character.h"

ACGun::ACGun()
{
    CHelpers::CreateComponent<USkeletalMeshComponent>(this, &mesh, "SkeletalMesh");
    RootComponent = mesh;


}

ACGun *ACGun::CreateWeapon(UWorld *world, TSubclassOf<class ACWeapon> classof, ACharacter *owner)
{
    FActorSpawnParameters params;
    params.Owner = owner;

    //이부분이 Weapon?
    ACGun *temp = world->SpawnActor<ACGun>(classof, params);
    temp->AttachToComponent(owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
                            temp->mAttachBone);
    return temp;
}
