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
   
    
    switch (FireType)
    {
    case E_Gun::Rifle: 
    {
        ACBullet *temp = ACBulletManager::GetInstance().Pop();
        if (!!world)
        {
            if (!!temp)
            {
                if (direction.Normalize())
                {
                    temp->SetActorLocation(start);
                    temp->SetActorRotation(direction.Rotation());
                    temp->Fire(direction);
                }
            }
            else
                CLog::Print("temp is nullptr");
        }
    }

        break;
    case E_Gun::ShotGun: 
    {
        FVector randirection1 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 0.1f, 0.1f);
        FVector randirection2 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 10.1f, 0.1f);
        FVector randirection3 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 20.1f, 0.1f);
        FVector randirection4 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 1.f, 10.1f);
        FVector randirection5 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 0.1f, 20.1f);
        FVector randirection6 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 15.1f, 15.1f);
        FVector randirection7 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 30.f, 30.1f);
        FVector randirection8 = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(direction, 45.f, 45.1f);
            
        ACBullet *temp1 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp2 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp3 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp4 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp5 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp6 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp7 = ACBulletManager::GetInstance().Pop();
        ACBullet *temp8 = ACBulletManager::GetInstance().Pop();
       
        if (!!temp1 && !!temp2 && !!temp3 && !!temp4 && !!temp5 && !!temp6 && !!temp7 && !!temp8)
        {

            if (direction.Normalize())
            {
                temp1->SetActorLocation(start);
                temp1->SetActorRotation(randirection1.Rotation());
                temp1->Fire(randirection1);
                temp2->SetActorLocation(start);
                temp2->SetActorRotation(randirection2.Rotation());
                temp2->Fire(randirection2);
                temp3->SetActorLocation(start);
                temp3->SetActorRotation(randirection3.Rotation());
                temp3->Fire(randirection3);
                temp4->SetActorLocation(start);
                temp4->SetActorRotation(randirection4.Rotation());
                temp4->Fire(randirection4);
                temp5->SetActorLocation(start);
                temp5->SetActorRotation(randirection5.Rotation());
                temp5->Fire(randirection5);
                temp6->SetActorLocation(start);
                temp6->SetActorRotation(randirection6.Rotation());
                temp6->Fire(randirection6);
                temp7->SetActorLocation(start);
                temp7->SetActorRotation(randirection7.Rotation());
                temp7->Fire(randirection7);
                temp8->SetActorLocation(start);
                temp8->SetActorRotation(randirection8.Rotation());
                temp8->Fire(randirection8);
            }
        }
            

    }

        break;
    case E_Gun::Sniper:
    {
    }

        break;

    default:
        break;
    }
    /*ACBullet *temp = ACBulletManager::GetInstance().Pop();
    if (!!world)
    {
        if (!!temp)
        {
            if (direction.Normalize())
            {
                temp->SetActorLocation(start);
                temp->SetActorRotation(direction.Rotation());
                temp->Fire(direction);
            }
        }
        else
            CLog::Print("temp is nullptr");
    }*/


    UGameplayStatics::SpawnEmitterAttached(FlashParticle, mesh, "MuzzleFlash", FVector::ZeroVector,
                                           FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
    UGameplayStatics::SpawnEmitterAttached(EjectParticle, mesh, "AmmoEject", FVector::ZeroVector, FRotator::ZeroRotator,
                                           EAttachLocation::KeepRelativeOffset);
}

