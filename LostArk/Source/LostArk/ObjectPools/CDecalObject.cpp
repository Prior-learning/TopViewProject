#include "CDecalObject.h"
#include "Components/DecalComponent.h"
#include "CParticleManager.h"
#include "../UParticlePooling.h"


ACDecalObject::ACDecalObject()
{
   
}


void ACDecalObject::SetDecalInfo(const EDecalShape &shape, const FRotator &direction, const float degree,
                                 const FVector &location, const float circum, const float distancefromtcenter)
{
    SetActorLocation(location);
    mShape = shape;
    mDirection = direction;
    mDegree = degree;
   
    mCircum = circum;
    mArea = 0;
    mEraseArea = distancefromtcenter;

    SetActorRotation(FQuat(mDirection));
    ShowDecal();
}
void ACDecalObject::SetDecalInfo(FDecalInfo &info)
{
    SetActorLocation(info.location);
    mShape = info.shape;
    mDirection = info.direction;
    mDegree = info.degree;

    mCircum = info.circum;
    mArea = 0;
    mEraseArea = info.distancefromtcenter;

    SetActorRotation(FQuat(mDirection));
    ShowDecal();

    mInfo = info;
}
void ACDecalObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDecalObject::SpawnParticle()
{
    ensureMsgf(mParticle != nullptr, TEXT("Decal has not ParticleSystem"));
    if (!!mParticle)
    {
        Fdir = -GetActorForwardVector().GetSafeNormal2D();
        Rdir = -GetActorRightVector().GetSafeNormal2D();

        switch (mShape)
        {
        case EDecalShape::Circle:
            CircleParticle();
            break;
        case EDecalShape::Triangle:


            AUParticlePooling *particle = ACParticleManager::Get().GetParticle();
            particle->SetActorLocation(GetActorLocation());
            particle->SetParticle(mParticle);
            TriangleParticle(GetActorLocation(), 3);
            

            break;
        }
       
    }
}

void ACDecalObject::CircleParticle()
{
    int AngleAxis = 0;
    float distance = 300.f;
    AUParticlePooling *particle;
    // prevent number from growind indefinitely
    while(AngleAxis != 360)
    {
        AngleAxis += 30;
        FVector location = GetActorLocation();
        FVector RotateValue = GetActorLocation().RotateAngleAxis(AngleAxis, FVector(0, 0, 1));
        RotateValue = RotateValue.GetSafeNormal2D() * distance;
        location.X += RotateValue.X; 
        location.Y += RotateValue.Y;
        //location.Z += RotateValue.Z;

        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mParticle);
    }
}

void ACDecalObject::TriangleParticle(FVector loc, int level)
{
    level--;
    if (level == 0)
        return;

    FVector location = loc;
    AUParticlePooling *particle;
    // left
    {
        location += Fdir * 150;
        location += Rdir * 100.f;
        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mParticle);
        TriangleParticle(location, level);
    }
    //Right
    {
        location -= Rdir * 100.f * 2;
        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mParticle);
        TriangleParticle(location, level);
    }
   
}
