#include "CPSkillComponent.h"
#include "../Global.h"
#include "../Skill/COnSkill.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "CPlayerStateComponent.h"

UCPSkillComponent::UCPSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    CurrentSkilltype = -1;
}

void UCPSkillComponent::OnFSkillUsed()
{
    SlotInfo[0].bInCoolDown = true;

        OnSlotInfoChanged.Broadcast(0);
}

void UCPSkillComponent::OnESkillUsed()
{
        SlotInfo[1].bInCoolDown = true;

    OnSlotInfoChanged.Broadcast(1);
}

void UCPSkillComponent::OnQSkillUsed()
{
        SlotInfo[0].bInCoolDown = true;

    OnSlotInfoChanged.Broadcast(2);
}

void UCPSkillComponent::OnRSkillUsed()
{
        SlotInfo[0].bInCoolDown = true;

    OnSlotInfoChanged.Broadcast(3);
}

void UCPSkillComponent::OnTSkillUsed()
{
     SlotInfo[0].bInCoolDown = true;

    OnSlotInfoChanged.Broadcast(4);
}

void UCPSkillComponent::BeginPlay()
{
	Super::BeginPlay();

    SkillBind.Add(ESkillButton::F, ESkill_Type::TargetDown);
    SkillBind.Add(ESkillButton::E, ESkill_Type::ShotGun);

    ACharacter *character = Cast<ACharacter>(GetOwner());
    for (int32 i = 0; i < (int32)ESkill_Type::Max; i++)
    {
        if (!!Datas[i])
        {
           Datas[i]->BeginPlay(character);
           OnSkills[i] = Datas[i]->GetOnSkill();
           if (!!OnSkills[i])
           {
               SlotInfo[i].bInCoolDown = false;
               SlotInfo[i].CoolTime = OnSkills[i]->GetDatas()[0].SkillCoolDown;
           }
        }
       // SetData 함수를 통해 스킬 종류별로 초기화... BP에서 데이타 에셋 넣어주면 됌.
    }
    OnSkills[0]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnFSkillUsed);
    OnSkills[1]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnESkillUsed);
   /* OnSkills[2]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnQSkillUsed);
    OnSkills[3]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnRSkillUsed);
    OnSkills[4]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnTSkillUsed);*/
}

void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCPSkillComponent::OnSkill(ESkillButton InButton)
{
    ESkill_Type *SkillType = SkillBind.Find(InButton);
    //버튼을 Key로 만든 맵에 있는 value값을 임시로 저장해 Datas 배열내에 있는 스킬정보를 찾아 OnSkill
    if (!!SkillType &&!! Datas[(int32)(*SkillType)])
    {
        CurrentSkilltype = (int)SkillBind[InButton];

        // COnSkill 에 Skilldata가 멤버변수로 있음.GetOnSkill 함수는 skillData 클래스에 있음
       /* ACOnSkill *action = Datas[(int32)(*SkillType)]->GetOnSkill();
        if (!!action)
        {
            action->OnSkill();
        }*/
        if (OnSkills[(int32)(*SkillType)])
            OnSkills[(int32)(*SkillType)]->OnSkill();
    }
}

