#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICombat.generated.h"

UINTERFACE(MinimalAPI)
class UICombat : public UInterface
{
    GENERATED_BODY()
};


class LOSTARK_API IICombat
{
    GENERATED_BODY()
  public:
    virtual void CreateWeapon() = 0;

    virtual void OnCollision() = 0;
    virtual void OffCollision() = 0;
    virtual void Attack() = 0;
    virtual void Damaged(float Damage, FDamageEvent &Event, AController *controller, AActor *causer,
                         const FVector hitLocation, class UParticleSystem *particle) = 0;
};
