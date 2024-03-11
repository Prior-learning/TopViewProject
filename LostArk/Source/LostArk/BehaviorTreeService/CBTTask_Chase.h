#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTask_Chase.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UCBTTask_Chase : public UBTTaskNode
{
	GENERATED_BODY()

  public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

	private:
	 int mRadius = 1000;
};
