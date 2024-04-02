#include "CPSkillComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"


UCPSkillComponent::UCPSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
}
void UCPSkillComponent::BeginPlay()
{
	Super::BeginPlay();
    CheckNull(SkillDataTable);
    TArray<FSkillData *> datas;
    SkillDataTable->GetAllRows<FSkillData>("", datas);

    for (int32 i = 0; i < (int8)E_Skill::Max; i++)
    {
        for (FSkillData *data : datas)
        {
            if ((E_Skill)i == data->Skill)
            {
                Datas[i] = data;

                continue;
            }
        }
    }
}
void UCPSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    for (int32 i = 0; i < (int8)E_Skill::Max; i++)
    {
        if (Datas[i]->bInCoolTime)
        {
            Datas[i]->SkillTimer -= DeltaTime;
            if (Datas[i]->SkillTimer<=0)
            {
                Datas[i]->SkillTimer = 0;
                Datas[i]->bInCoolTime = false;
            }
        
        }
    
    }
}

void UCPSkillComponent::DoSkill(E_Skill InSkill)
{
    CLog::Log("DoSkill Called");
    ACharacter *character = Cast<ACharacter>(GetOwner());

    const FSkillData *data = Datas[(int8)InSkill];
    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            if (!data->bInCoolTime)
            {
                character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
                Datas[(int8)InSkill]->bInCoolTime = true;
                Datas[(int8)InSkill]->SkillTimer = Datas[(int8)InSkill]->SkillCoolDown;
            }
        }
    }
}

