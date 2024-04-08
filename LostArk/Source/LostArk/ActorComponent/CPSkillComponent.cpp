#include "CPSkillComponent.h"
#include "../Global.h"
#include "../Skill/COnSkill.h"
#include "GameFramework/Character.h"
#include "CPlayerStateComponent.h"

UCPSkillComponent::UCPSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
}

void UCPSkillComponent::E_SkillBind()
{
}

void UCPSkillComponent::F_SkillBind()
{
}

void UCPSkillComponent::BeginPlay()
{
	Super::BeginPlay();

    SkillBind.Add(ESkillButton::F, ESkill_Type::TargetDown);
    SkillBind.Add(ESkillButton::E, ESkill_Type::ShotGun);

    //���� ��ų ���ε� �κ��� ���� UI�� �����ؼ� UI�� ����� ����.
    ACharacter *character = Cast<ACharacter>(GetOwner());
    for (int32 i = 0; i < (int32)ESkill_Type::Max; i++)
    {
        if (!!Datas[i])
            Datas[i]->BeginPlay(character);
        //UCSkillData�迭���� ESkill_Type�� ������ŭ OnSkill �� �Ļ� Ŭ�������� SetData �Լ��� ���� ��ų �������� �ʱ�ȭ �ϴµ�... ����� �۵��Ϸ���?
    }
}

void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCPSkillComponent::OnSkill(ESkillButton InButton)
{
    ESkill_Type *SkillType = SkillBind.Find(InButton);
    //��ư�� Key�� ���� �ʿ� �ִ� value���� �ӽ÷� ������ Datas �迭���� �ִ� ��ų������ ã�� OnSkill
    if (!!SkillType &&!! Datas[(int32)(*SkillType)])
    {
        // COnSkill �� Skilldata�� ��������� ����.GetOnSkill �Լ��� skillData Ŭ������ ����
        ACOnSkill *action = Datas[(int32)(*SkillType)]->GetOnSkill();
        if (!!action)
            action->OnSkill();
    }
}

