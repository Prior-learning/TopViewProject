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

  protected:
    virtual void BeginPlay() override;



};


