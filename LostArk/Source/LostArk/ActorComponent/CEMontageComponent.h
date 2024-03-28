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


    bool GetKnockBack() {return bKnockBackable;}
  protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
    bool bKnockBackable = true;
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