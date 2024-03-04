#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CENotifyEndAction.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UCENotifyEndAction : public UAnimNotify
{
	GENERATED_BODY()
	
public:

    virtual FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
};
