#include "CENotifyDecal_Playerlocation.h"


FString UCENotifyDecal_Playerlocation::GetNotifyName() const
{
    return "DecalToPlayer";
}

void UCENotifyDecal_Playerlocation::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
 
    if (MeshComp == nullptr)
        return;
    if (MeshComp->GetOwner() == nullptr)
        return;
    if (ACDecalManager::Get() == nullptr)
        return;

    FVector forward = MeshComp->GetOwner()->GetActorForwardVector().GetSafeNormal2D();
   
    FRotator rot = MeshComp->GetOwner()->GetActorRotation();
        
    switch (mDirection)
    {
    case EDecalDirection::Forward:

        break;
    case EDecalDirection::Back:
        rot.Yaw += 180.f;
        break;
    case EDecalDirection::Right:
        rot.Yaw += 90.f;
        break;
    case EDecalDirection::Left:
        rot.Yaw -= 90.f;
        break;
    }

    mInfo.direction = rot;

    ACDecalManager::Get()->SetDecalInfo_LocationToPlayer(mInfo);
    
}
