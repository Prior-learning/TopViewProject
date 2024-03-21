#include "CDecalObject.h"
#include "Components/DecalComponent.h"

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

void ACDecalObject::BeginPlay()
{
	Super::BeginPlay();
	
}


