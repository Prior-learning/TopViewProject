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

void ACGun::Fire(ACharacter *owner)
{
    
    UWorld *world = GetWorld();

    FVector start, end, direction;
    direction = owner->GetActorForwardVector();
    FVector meshLocation = mesh->GetSocketLocation("MuzzleFlash");
    start = meshLocation + direction;
    FVector endDirection = direction * 2000;
    end = meshLocation + endDirection;
    if (world)
    {
        ACBullet *bullet = world->SpawnActor<ACBullet>(mBullet);
        if (bullet)
        {
            

            if (direction.Normalize())
            {
                bullet->SetActorLocation(start);
                bullet->SetActorRotation(direction.Rotation());
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

