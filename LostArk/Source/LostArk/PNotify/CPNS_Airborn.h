#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CPNS_Airborn.generated.h"


UCLASS()
class LOSTARK_API UCPNS_Airborn : public UAnimNotifyState
{
	GENERATED_BODY()

	public:
    FString GetNotifyName_Implementation() const override;

    virtual void NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation,float TotalDuration) override;
    virtual void NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;
	
};
