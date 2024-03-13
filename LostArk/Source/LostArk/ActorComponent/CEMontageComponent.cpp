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

    // Notify -> 다른 montage 실행이 안됌
    // NotifyState-> 이건 다른걸로 해도 되더라구요

    const FMontageData *data = Datas[(int16)InState];
    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
        }
    }
}

