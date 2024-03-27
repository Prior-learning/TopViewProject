#include "CNotifyState_Breaker.h"
#include "../ActorComponent/CBreakerComponent.h"
#include "../Global.h"

FString UCNotifyState_Breaker::GetNotifyName_Implementation()
{
    return "Breaker Trigger";
}

void UCNotifyState_Breaker::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
                                        float TotalDuration)
{
    breakcomp = CHelpers::GetComponent<UCBreakerComponent>(MeshComp->GetOwner());
    CheckNull(breakcomp);
    breakcomp->OnBoxOverlap();
    
}

void UCNotifyState_Breaker::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    CheckNull(breakcomp);
    breakcomp->OnBoxOverlap();
}
