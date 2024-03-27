#include "CEMontageComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"


void UCEMontageComponent::BeginPlay()
{
    Super::BeginPlay();
    CheckNull(DataTable);
    TArray<FMontageData *> datas;
    DataTable->GetAllRows<FMontageData>("", datas);


    // 데이터가 들어있는 만큼 검사를하고

    for (int32 i = 0; i < datas.Num(); i++)
    {
        for (FMontageData *data : datas)
        {
            Datas2[int8(data->Type)].Emplace(data);
        }
    }
}

void UCEMontageComponent::PlayAnimMontage(EMontage_State InState)
{

    ACharacter *character = Cast<ACharacter>(GetOwner());

    CheckTrue(Datas2[(int8)InState].Num() == 0);
  
    int idx = rand() % Datas2[(int8)InState].Num();
    const FMontageData *data = Datas2[(int8)InState][idx];

    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
            
        }
    }
}

