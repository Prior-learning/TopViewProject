#include "CPSkillComponent.h"
#include "../Global.h"
#include "../Skill/COnSkill.h"
#include "GameFramework/Character.h"
#include "CPlayerStateComponent.h"

UCPSkillComponent::UCPSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
}

void UCPSkillComponent::BeginPlay()
{
	Super::BeginPlay();

    SkillBind.Add(ESkillButton::F, ESkill_Type::TargetDown);
    //���� ��ų ���ε� �κ��� ���� UI�� �����ؼ� UI�� ����� ����.
    ACharacter *character = Cast<ACharacter>(GetOwner());
    for (int32 i = 0; i < (int32)ESkill_Type::Max; i++)
    {
        if (!!Datas[i])
            Datas[i]->BeginPlay(character);
    }
    // SkillData Ŭ������ ���ǵ� ESkill_Type�� ������ŭ �迭 �ʱ�ȭ,���� ��ü�� Ÿ���� COnSkill�� �Ļ�Ŭ������

    
}

void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCPSkillComponent::OnSkill(ESkillButton InButton)
{
    ESkill_Type *SkillType = SkillBind.Find(InButton);

    if (!!SkillType &&!! Datas[(int32)(*SkillType)])
    {
        // COnSkill �� Skilldata�� ��������� ����.GetOnSkill �Լ��� skillData Ŭ������ ����
        ACOnSkill *action = Datas[(int32)(*SkillType)]->GetOnSkill();
        if (!!action)
            action->OnSkill();
    }
    
}

