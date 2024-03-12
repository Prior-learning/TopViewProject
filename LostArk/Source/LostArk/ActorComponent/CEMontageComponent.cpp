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

    CLog::Log("Hitted Called");
    const FMontageData *data = Datas[(int16)InState];
    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            CLog::Log("Montage Called");
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
        }
    }
}

