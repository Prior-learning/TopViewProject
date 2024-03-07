#include "CGun.h"
#include "../Global.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/Character.h"

ACGun::ACGun()
{
    CHelpers::CreateComponent<USkeletalMeshComponent>(this, &mesh, "SkeletalMesh");
   
    RootComponent = mesh;
    FireRate = 0.15f;

}

ACGun *ACGun::CreateWeapon(UWorld *world, TSubclassOf<class ACWeapon> classof, ACharacter *owner)
{
    FActorSpawnParameters params;
    params.Owner = owner;

    //이부분이 Weapon?
    ACGun *temp = world->SpawnActor<ACGun>(classof, params);
    temp->AttachToComponent(owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
                            temp->mRifleHolster);
    return temp;
}

void ACGun::Fire()
{
    UGameplayStatics::SpawnEmitterAttached(FlashParticle, mesh, "MuzzleFlash", FVector::ZeroVector,FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
    UGameplayStatics::SpawnEmitterAttached(EjectParticle, mesh, "AmmoEject", FVector::ZeroVector,FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
    //FVector muzzleLocation = mesh->GetSocketLocation("MuzzleFlash");
    //UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation, 0.6f, 0.8f);
}

