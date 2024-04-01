#include "CEMontageComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"


void UCEMontageComponent::BeginPlay()
{
    Super::BeginPlay();
    CheckTrue(mPhaseDataTable.Num() == 0);
    DataTableInit();
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

    if (InState == EMontage_State::Skill)
    {
        mPhase++;
        DataTableInit();
    }

}

void UCEMontageComponent::DataTableInit()
{

    CheckNull(mPhaseDataTable[mPhase]);

    TArray<FMontageData *> datas;

    mPhaseDataTable[mPhase]->GetAllRows<FMontageData>("", datas);
    // �����Ͱ� ����ִ� ��ŭ �˻縦�ϰ�
       
    for (FMontageData *data : datas)
    {
        Datas2[int8(data->Type)].Emplace(data);
    }
        
    

  

}

