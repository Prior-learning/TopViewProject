#include "CPSkillComponent.h"
#include "../Global.h"

#include "../Skill/COnSkill.h"
#include "../Skill/CSkillData.h"

#include "GameFramework/Character.h"
#include "CPlayerStateComponent.h"


UCPSkillComponent::UCPSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
}

void UCPSkillComponent::BeginPlay()
{
	Super::BeginPlay();
    ACharacter *character = Cast<ACharacter>(GetOwner());
    /*for (int32 i = 0; i < (int32)ESkill::Max; i++)
    {
        if (!!Datas[i])
            Datas[i]->BeginPlay(character);
    }*/
    
}
void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

   
}
void UCPSkillComponent::OnSkill()
{
    /*if (!!Datas[(int32)mSkill])
    {
        ACOnSkill *action = Datas[(int32)mSkill]->GetOnSkill();

        if (!!action)
            action->OnSkill();
    }*/
}

