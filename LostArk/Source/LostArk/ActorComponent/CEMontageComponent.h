#pragma once

#include "CoreMinimal.h"
#include "CMontageComponent.h"
#include "CEMontageComponent.generated.h"



UENUM()
enum class EMontage_State : uint16
{
    Attack,
    Hitted,
    Roll,
    Reload,
    Dead,
    Max
};

UCLASS()
class LOSTARK_API UCEMontageComponent : public UCMontageComponent
{
    GENERATED_BODY()
  public:
    UCEMontageComponent() = default;

  protected:
    virtual void BeginPlay() override;



};


