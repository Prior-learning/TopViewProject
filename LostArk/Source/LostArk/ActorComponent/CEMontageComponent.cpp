#include "CEMontageComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"

void UCEMontageComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCEMontageComponent::PlayAnimMontage(EMontage_State InState)
{
    ACharacter *character = Cast<ACharacter>(GetOwner());

    // Notify -> �ٸ� montage ������ �ȉ�
    // NotifyState-> �̰� �ٸ��ɷ� �ص� �Ǵ��󱸿�

    const FMontageData *data = Datas[(int16)InState];
    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
        }
    }
}

