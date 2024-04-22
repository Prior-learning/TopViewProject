#include "CEMontageComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"


void UCEMontageComponent::BeginPlay()
{
    Super::BeginPlay();
    DataTableInit();
    
}

void UCEMontageComponent::PlayAnimMontage(EMontage_State InState)
{
    
    ACharacter *character = Cast<ACharacter>(GetOwner());
    CLog::Print("Called Montage");
    CheckTrue(Datas2[(int8)InState].Num() == 0);
    CLog::Print("is not empty Montage");
    int idx = rand() % Datas2[(int8)InState].Num();
    const FMontageData *data = Datas2[(int8)InState][idx];

    if (!!data)
    {
        if (!!data->AnimMontage)
        {
            character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
            
        }
    }
    else
        CLog::Print("data is empty ");

    if (InState == EMontage_State::Skill)
    {
        mPhase++;
        DataTableInit();

    }

}

void UCEMontageComponent::DataTableInit()
{

 
    TArray<FMontageData *> datas;
    mPhaseDataTable[mPhase]->GetAllRows<FMontageData>("", datas);
    // 데이터가 들어있는 만큼 검사를하고
       
    for (FMontageData *data : datas)
    {
        Datas2[int8(data->Type)].Emplace(data);
    }
        
    

  

}

