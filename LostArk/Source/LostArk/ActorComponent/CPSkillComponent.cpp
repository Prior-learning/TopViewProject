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
    SlotInfo[0].CoolTime = OnSkills[0]->GetDatas()[0].SkillCoolDown;
    if (SendSlotInfo.IsBound())
        SendSlotInfo.Broadcast(0, SlotInfo[0].CoolTime);
}

void UCPSkillComponent::OnESkillUsed()
{
    SlotInfo[1].bInCoolDown = true;
    SlotInfo[1].CoolTime = OnSkills[1]->GetDatas()[0].SkillCoolDown;

    UE_LOG(LogTemp, Warning, TEXT("[SkillComponent::EUsed]"));
    if (SendSlotInfo.IsBound())
        SendSlotInfo.Broadcast(1, SlotInfo[0].CoolTime);
}

void UCPSkillComponent::OnQSkillUsed()
{
    SlotInfo[0].bInCoolDown = true;
}

void UCPSkillComponent::OnRSkillUsed()
{
    SlotInfo[0].bInCoolDown = true;
}

void UCPSkillComponent::OnTSkillUsed()
{
    SlotInfo[0].bInCoolDown = true;
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
    OnSkills[0]->OnSkillUsed.AddUFunction(this, FName("OnFSkillUsed"));
    OnSkills[1]->OnSkillUsed.AddUFunction(this, FName("OnESkillUsed"));
   /* OnSkills[2]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnQSkillUsed);
    OnSkills[3]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnRSkillUsed);
    OnSkills[4]->OnSkillUsed.AddUObject(this, &UCPSkillComponent::OnTSkillUsed);*/
}

void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(SlotInfo[0].bInCoolDown)
    {
        float PreviousCoolTime = SlotInfo[0].CoolTime;
        SlotInfo[0].CoolTime -= DeltaTime;
        // 이전 쿨타임과 현재 쿨타임을 비교하여 1초 간격으로 감소하는 순간을 찾음
        if (FMath::FloorToInt(PreviousCoolTime) != FMath::FloorToInt(SlotInfo[0].CoolTime))
        {
            if (UpdateCoolTime.IsBound())
                UpdateCoolTime.Broadcast(0,FMath::FloorToInt(SlotInfo[0].CoolTime));

            // 쿨타임이 0이 되면 마지막으로 한 번 더 업데이트
            if (SlotInfo[0].CoolTime <= 0)
            {
                if (UpdateCoolTime.IsBound())
                    UpdateCoolTime.Broadcast(0,FMath::FloorToInt(0));
            }
        }
    }
    if (SlotInfo[1].bInCoolDown)
    {
        float PreviousCoolTime = SlotInfo[1].CoolTime;
        SlotInfo[1].CoolTime -= DeltaTime;
        if (FMath::FloorToInt(PreviousCoolTime) != FMath::FloorToInt(SlotInfo[0].CoolTime))
        {
            if (UpdateCoolTime.IsBound())
                UpdateCoolTime.Broadcast(1, FMath::FloorToInt(SlotInfo[1].CoolTime));
            if (SlotInfo[1].CoolTime <= 0)
            {
                if (UpdateCoolTime.IsBound())
                    UpdateCoolTime.Broadcast(1, FMath::FloorToInt(0));
            }
        }
    }

}

void UCPSkillComponent::OnSkill(ESkillButton InButton)
{
    ESkill_Type *SkillType = SkillBind.Find(InButton);
    //버튼을 Key로 만든 맵에 있는 value값을 임시로 저장해 Datas 배열내에 있는 스킬정보를 찾아 OnSkill
    if (!!SkillType &&!! Datas[(int32)(*SkillType)])
    {
        CurrentSkilltype = (int)SkillBind[InButton];
        // COnSkill 에 Skilldata가 멤버변수로 있음.GetOnSkill 함수는 skillData 클래스에 있음
        if (OnSkills[(int32)(*SkillType)])
            OnSkills[(int32)(*SkillType)]->OnSkill();
    }
}

 /* ACOnSkill *action = Datas[(int32)(*SkillType)]->GetOnSkill();
       if (!!action)
       {
           action->OnSkill();
       }*/