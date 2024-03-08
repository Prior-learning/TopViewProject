#include "CGun.h"
#include "../Global.h"
#include "Particles/ParticleSystem.h"
#include "CBullet.h"
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

void ACGun::Fire(ACharacter *owner)
{
    
    UWorld *world = GetWorld();

    FVector start, end, direction;
    //방향
    direction = owner->GetActorForwardVector();
    FTransform transform = mesh->GetComponentToWorld();
    FVector meshLocation = transform.GetLocation();
    start = meshLocation + direction;
    FVector endDirection = direction * 1000;
    end = meshLocation + endDirection;
    if (world)
    {
        ACBullet *bullet = world->SpawnActor<ACBullet>(mBullet);
        if (bullet)
        {
            bullet->SetActorLocation(start);
            bullet->SetActorRotation(direction.Rotation());

            if (direction.Normalize())
            {
                // 정규화에 성공하면 Fire 함수에 넣어준다.
                bullet->Fire(direction);
            }

        }
    }

    UGameplayStatics::SpawnEmitterAttached(FlashParticle, mesh, "MuzzleFlash", FVector::ZeroVector,
                                           FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
    UGameplayStatics::SpawnEmitterAttached(EjectParticle, mesh, "AmmoEject", FVector::ZeroVector, FRotator::ZeroRotator,
                                           EAttachLocation::KeepRelativeOffset);
    /* float AlphaOffset = Fireoffset;
    if (AlphaOffset < 1.f)
        AlphaOffset = 1.01f;
    FVector conDirection =
        UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(OutDirection, 1.0f, AlphaOffset);
    conDirection *= 3000.0f;*/
    //FVector muzzleLocation = mesh->GetSocketLocation("MuzzleFlash");
    //UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSoundCue, muzzleLocation, 0.6f, 0.8f);
}

