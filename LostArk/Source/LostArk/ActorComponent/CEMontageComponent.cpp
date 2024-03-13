#include "CEMontageComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"


void UCEMontageComponent::BeginPlay()
{
    Super::BeginPlay();
    CheckNull(DataTable);
    TArray<FMontageData *> datas;
    DataTable->GetAllRows<FMontageData>("", datas);

    for (int32 i = 0; i < datas.Num(); i++)
    {
        for (FMontageData *data : datas)
        {
            Datas2[int16(data->Type)].Emplace(data);
        }
    }
}

void UCEMontageComponent::PlayAnimMontage(EMontage_State InState)
{
    ACharacter *character = Cast<ACharacter>(GetOwner());

    int idx = rand() % Datas2[(int16)InState].Num();
    const FMontageData *data = Datas2[(int16)InState][idx];

    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
        }
    }
}

