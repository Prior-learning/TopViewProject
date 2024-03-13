#include "CBTTask_Arrive.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <cmath>
#include "../Global.h"
#include "AIController.h"
#include "../ActorComponent/CEnemyStateComponent.h"

EBTNodeResult::Type UCBTTask_Arrive::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    FVector movepos = OwnerComp.GetBlackboardComponent()->GetValueAsVector("MovePos");
    AActor* self = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Self"));
    UCEnemyStateComponent* statecomp = CHelpers::GetComponent<UCEnemyStateComponent>(self);

    if (!!self)
    {
        FVector current = self->GetActorLocation();

        float distance = sqrt(pow(movepos.X - current.X, 2) + pow(movepos.Y - current.Y, 2));
        if (distance <= mNearDistance)
        {
            statecomp->Remove(E_WHY_BLOCKED::MOVE);
            statecomp->SetMode(EStateEnemyType::Idle, E_WHY_BLOCKED::NONE);
            return EBTNodeResult::Succeeded;
        }
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}