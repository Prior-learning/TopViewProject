#include "CDecalObject.h"
#include "Components/DecalComponent.h"

ACDecalObject::ACDecalObject()
{
   
}


void ACDecalObject::SetDecalInfo(EDecalShape &shape, FVector &location, float circum, float distancefromtcenter,
                                 float timer)
{
    SetActorLocation(location);
    mShape = shape;
    mTimer = timer;
    mCircum = circum;
    mArea = 0;
    mEraseArea = distancefromtcenter;
    ShowDecal();
}

void ACDecalObject::BeginPlay()
{
	Super::BeginPlay();
	
}


