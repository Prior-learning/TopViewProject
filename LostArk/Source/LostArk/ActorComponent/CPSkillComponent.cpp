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

    //위의 스킬 바인드 부분은 추후 UI와 연계해서 UI로 등록할 예정.
    ACharacter *character = Cast<ACharacter>(GetOwner());
    for (int32 i = 0; i < (int32)ESkill_Type::Max; i++)
    {
        if (!!Datas[i])
            Datas[i]->BeginPlay(character);
        //UCSkillData배열내에 ESkill_Type의 갯수만큼 OnSkill 의 파생 클래스들의 SetData 함수를 통해 스킬 종류별로 초기화 하는데... 제대로 작동하려나?
    }
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
        // COnSkill 에 Skilldata가 멤버변수로 있음.GetOnSkill 함수는 skillData 클래스에 있음
        ACOnSkill *action = Datas[(int32)(*SkillType)]->GetOnSkill();
        if (!!action)
            action->OnSkill();
    }
}

