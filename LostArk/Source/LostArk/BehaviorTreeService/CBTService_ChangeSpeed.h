#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UCBTService_ChangeSpeed : public UBTService
{
	GENERATED_BODY()
	
	public:
        UCBTService_ChangeSpeed();

    protected:
        virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

	public:
        UPROPERTY(BlueprintReadWrite, EditAnywhere)
            float mSpeed = 1.f;
       

};
