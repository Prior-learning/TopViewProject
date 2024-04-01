#pragma once

#include "CoreMinimal.h"
#include "CMontageComponent.h"
#include "CEMontageComponent.generated.h"


UCLASS()
class LOSTARK_API UCEMontageComponent : public UCMontageComponent
{
    GENERATED_BODY()
  public:
    UCEMontageComponent() = default;

  public:
    virtual void BeginPlay() override;

    virtual void PlayAnimMontage(EMontage_State InState);

    void DataTableInit();

    bool GetKnockBack() {return bKnockBackable;}

  private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Status",meta=(AllowPrivateAccess=true))
    bool bKnockBackable = true;

    UPROPERTY(EditDefaultsOnly, Category="DataTable",meta=(AllowPrivateAccess=true))
    TArray<UDataTable *> mPhaseDataTable;

    
    TArray<FMontageData *> Datas2 [(int16)EMontage_State::Max];

    UPROPERTY(meta=(AllowPrivateAccess=true))
    int32 mPhase;
};


/* //Roll map 자료형으로 왜 여러개 필요하지?
* Aim Hit, Attacking
* P_State =   Hit + Attacking 
* Hit = 0
* 
* 
* P_State[idle] = 0010; + Roll - Roll
* P_State[Attack] = 0010; +Roll - Roll
* P_State[Aim] = 0010;    + Roll - Roll
* P_State[Roll] = 0010;   + Roll - Rooll
*/