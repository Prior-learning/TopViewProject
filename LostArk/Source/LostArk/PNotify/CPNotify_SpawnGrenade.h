#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPNotify_SpawnGrenade.generated.h"

UCLASS()
class LOSTARK_API UCPNotify_SpawnGrenade : public UAnimNotify
{
	GENERATED_BODY()

		
  public:
    FString GetNotifyName_Implementation() const override;

    virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

  protected:
    UPROPERTY(BlueprintReadOnly)
    class UCPSkillComponent *mSkill;
	
};
