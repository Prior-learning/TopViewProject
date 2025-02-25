#include "CENotifyDecal.h"


FString UCENotifyDecal::GetNotifyName() const
{
    return "Decal";
}
void UCENotifyDecal::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (MeshComp == nullptr)
        return;
    if (MeshComp->GetOwner() == nullptr)
        return;
    if (ACDecalManager::Get() == nullptr)
        return;

    FVector forward = MeshComp->GetOwner()->GetActorForwardVector().GetSafeNormal2D();
    FVector location = MeshComp->GetOwner()->GetActorLocation() + forward * mOffset.X; 
    location.Z = -250.f + mOffset.Z;
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

    mInfo.location = location;
    mInfo.direction = rot;

    ACDecalManager::Get()->SetDecalInfo(mInfo);
    

    
}