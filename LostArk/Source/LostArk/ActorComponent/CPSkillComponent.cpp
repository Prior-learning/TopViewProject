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
    //위의 스킬 바인드 부분은 추후 UI와 연계해서 UI로 등록할 예정.
    ACharacter *character = Cast<ACharacter>(GetOwner());
    for (int32 i = 0; i < (int32)ESkill_Type::Max; i++)
    {
        if (!!Datas[i])
            Datas[i]->BeginPlay(character);
    }
    // SkillData 클래스에 정의된 ESkill_Type의 개수만큼 배열 초기화,들어가는 객체의 타입은 COnSkill의 파생클래스들

    
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
        // COnSkill 에 Skilldata가 멤버변수로 있음.GetOnSkill 함수는 skillData 클래스에 있음
        ACOnSkill *action = Datas[(int32)(*SkillType)]->GetOnSkill();
        if (!!action)
            action->OnSkill();
    }
    
}

