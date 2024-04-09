#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISkillNotify.generated.h"

UINTERFACE(MinimalAPI)
class UISkillNotify : public UInterface
{
	GENERATED_BODY()
};


class LOSTARK_API IISkillNotify
{
	GENERATED_BODY()

public:
    virtual void SpawnMesh() = 0;
    virtual void OnTrigger() = 0;

    
};
