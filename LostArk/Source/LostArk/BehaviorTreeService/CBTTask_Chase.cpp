#include "CBTTask_Chase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"


EBTNodeResult::Type UCBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	int8 operation = OwnerComp.GetBlackboardComponent()->GetValueAsEnum("State");
    FVector movepos = UKismetMathLibrary::RandomUnitVectorInConeInRadians(
        OwnerComp.GetBlackboardComponent()->GetValueAsVector("HomePos"), 100);
	switch (operation)
    {
        case 0:
            OwnerComp.GetBlackboardComponent()->SetValueAsEnum("State",1);
            
            movepos.Z = 0;

            OwnerComp.GetBlackboardComponent()->SetValueAsVector("MovePos", movepos * (rand() % mRadius));
            return EBTNodeResult::Succeeded;

        default:
            return EBTNodeResult::Failed;
    }

}