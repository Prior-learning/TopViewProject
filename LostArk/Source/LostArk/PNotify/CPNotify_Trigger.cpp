#include "CPNotify_Trigger.h"
#include "../Global.h"
#include "../ActorComponent/CPSkillComponent.h"
#include "../Skill/COnSkill.h"
#include "../Skill/ISkillNotify.h"




FString UCPNotify_Trigger::GetNotifyName_Implementation() const
{
    return "Trigger";
}

void UCPNotify_Trigger::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    mSkill = CHelpers::GetComponent<UCPSkillComponent>(MeshComp->GetOwner());
    CheckNull(mSkill);

    ACOnSkill *OnSkill;
    OnSkill = mSkill->GetData(1)->GetOnSkill();
    CheckNull(OnSkill);
    IISkillNotify *iSkill = Cast<IISkillNotify>(OnSkill);
    iSkill->OnTrigger();
}

