#include "CBTTask_Arrive.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <cmath>
#include "../Utilities/CLog.h"
#include "AIController.h"

EBTNodeResult::Type UCBTTask_Arrive::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    FVector movepos = OwnerComp.GetBlackboardComponent()->GetValueAsVector("MovePos");
    AActor* self = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Self"));
    if (!!self)
    {
        FVector current = self->GetActorLocation();

        float distance = sqrt(pow(movepos.X - current.X, 2) + pow(movepos.Y - current.Y, 2));
        CLog::Print(current);
        if (distance <= mNearDistance)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsEnum("State", 0);
            CLog::Log("Arrive");
            return EBTNodeResult::Succeeded;
        }
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}