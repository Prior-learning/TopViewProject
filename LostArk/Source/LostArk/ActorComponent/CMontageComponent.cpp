#include "CMontageComponent.h"
#include "LostArk/Global.h"
#include "GameFramework/Character.h"



UCMontageComponent::UCMontageComponent()
{
}

void UCMontageComponent::BeginPlay()
{
   	Super::BeginPlay();
    CheckNull(DataTable);
    TArray<FMontageData *> datas;
    DataTable->GetAllRows<FMontageData>("", datas);

    for (int32 i = 0; i < (int16)EMontage_State::Max; i++)
    {
        for (FMontageData *data : datas)
        {
            if ((EMontage_State)i == data->Type)
            {
                Datas[i] = data;

                continue;
            }
        } // for(data)
    }     // for(i)
		
}


void UCMontageComponent::PlayAnimMontage(EMontage_State InState)
{
    ACharacter *character = Cast<ACharacter>(GetOwner());

    const FMontageData *data = Datas[(int16)InState];
    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
        }
    }
}



