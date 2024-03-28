#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CNotifyState_Breaker.generated.h"


UCLASS()
class LOSTARK_API UCNotifyState_Breaker : public UAnimNotifyState
{
    GENERATED_BODY()

    FString GetNotifyName_Implementation();

    virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,
                             float TotalDuration) override;

    virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

  private:
    UPROPERTY(meta = (AllowPrivateAccess = true))
    class UCBreakerComponent *breakcomp;
};
