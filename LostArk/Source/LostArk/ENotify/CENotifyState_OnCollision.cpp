
#include "CENotifyState_OnCollision.h"

#include "../Combat/ICombat.h"

FString UCENotifyState_OnCollision::GetNotifyName_Implementation() const
{
    return "Collision";
}

void UCENotifyState_OnCollision::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);

    IICombat* weapon = Cast<IICombat>(MeshComp->GetOwner());
    if(!!weapon)
        weapon->OnCollision();
    

}


void UCENotifyState_OnCollision::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    IICombat *weapon = Cast<IICombat>(MeshComp->GetOwner());
    if (!!weapon)
        weapon->OffCollision();
    
}
