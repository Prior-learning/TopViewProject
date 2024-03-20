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
    FVector forward = MeshComp->GetOwner()->GetActorForwardVector().GetSafeNormal2D();
    FVector location = MeshComp->GetOwner()->GetActorLocation() + forward * mOffset.X; 
    if (ACDecalManager::Get() == nullptr)
        return;
    ACDecalManager::Get()->SetDecalInfo(mShape, location, mCircum,mDistancefromCenter, mTimer);
}