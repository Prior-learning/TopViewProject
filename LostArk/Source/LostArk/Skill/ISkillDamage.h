#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISkillDamage.generated.h"

UINTERFACE(MinimalAPI)
class UISkillDamage : public UInterface
{
	GENERATED_BODY()
};

class LOSTARK_API IISkillDamage
{
	GENERATED_BODY()

public:
    virtual void Damaged(float Damage, FDamageEvent &Event, AController *controller, AActor *causer,
                         const FVector hitLocation, class UParticleSystem *particle) = 0;
};
