#include "CGun.h"
#include "../Global.h"
#include "Particles/ParticleSystem.h"
#include "CBullet.h"
#include "../ObjectPools/CBulletManager.h"
#include "GameFramework/Character.h"

ACGun::ACGun()
{
    CHelpers::CreateComponent<USkeletalMeshComponent>(this, &mesh, "SkeletalMesh");
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = mesh;
    FireRate = 0.15f;

}
void ACGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
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
        ACBullet *temp = ACBulletManager::GetInstance().Pop();
       // Bullettemp.Add(temp);
        if (temp)
        {
            if (direction.Normalize())
            {
                temp->SetActorLocation(start);
                temp->SetActorRotation(direction.Rotation());
                temp->Fire(direction);
               /* if (world->GetTimerManager().IsTimerActive(ReturnHandle))
                {
                    world->GetTimerManager().ClearTimer(ReturnHandle);
                }
                world->GetTimerManager().SetTimer(ReturnHandle, this, &ACGun::ReturnBullet(temp), 2.0f, true);*/
                //ACBulletManager::GetInstance().Return(temp);

            }
            
            
        }
    }

    UGameplayStatics::SpawnEmitterAttached(FlashParticle, mesh, "MuzzleFlash", FVector::ZeroVector,
                                           FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
    UGameplayStatics::SpawnEmitterAttached(EjectParticle, mesh, "AmmoEject", FVector::ZeroVector, FRotator::ZeroRotator,
                                           EAttachLocation::KeepRelativeOffset);
    
}

void ACGun::ReturnBullet(ACBullet *bullet)
{
    ACBulletManager::GetInstance().Return(bullet);
}


