#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPNotify_ReturnHand.generated.h"


UCLASS()
class LOSTARK_API UCPNotify_ReturnHand : public UAnimNotify
{
	GENERATED_BODY()

public:
    FString GetNotifyName_Implementation() const override;

    virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

	
};
