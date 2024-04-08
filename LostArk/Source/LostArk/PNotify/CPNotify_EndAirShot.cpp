#include "CPNotify_EndAirShot.h"
#include "../Global.h"
#include "../ActorComponent/CPSkillComponent.h"
#include "../Skill/COnSkill.h"



FString UCPNotify_EndAirShot::GetNotifyName_Implementation() const
{
    return "EndAirShot";
}

void UCPNotify_EndAirShot::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    mSkill = CHelpers::GetComponent<UCPSkillComponent>(MeshComp->GetOwner());
    CheckNull(mSkill);

    ACOnSkill *OnSkill;
    OnSkill = mSkill->GetData(1)->GetOnSkill();
    CheckNull(OnSkill);
    OnSkill->End_OnSkill();
}

