#include "CPNotify_BeginAirShot.h"
#include "../Global.h"
#include "../ActorComponent/CPSkillComponent.h"
#include "../Skill/COnSkill.h"



FString UCPNotify_BeginAirShot::GetNotifyName_Implementation() const
{
    return "BeginAirShot";
}

void UCPNotify_BeginAirShot::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    Super::Notify(MeshComp, Animation);
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    mSkill = CHelpers::GetComponent<UCPSkillComponent>(MeshComp->GetOwner());
    CheckNull(mSkill);
   
    ACOnSkill *OnSkill;
    OnSkill = mSkill->GetData(1)->GetOnSkill();
    CheckNull (OnSkill);
    OnSkill->Begin_OnSkill();
}