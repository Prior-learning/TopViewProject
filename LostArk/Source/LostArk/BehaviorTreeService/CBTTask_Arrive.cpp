#include "CBTTask_Arrive.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <cmath>
#include "../Global.h"
#include "AIController.h"
#include "../ActorComponent/CEnemyStateComponent.h"

EBTNodeResult::Type UCBTTask_Arrive::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    FVector movepos = OwnerComp.GetBlackboardComponent()->GetValueAsVector("MovePos");
   
    AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(mtarget));
    if (!!target)
    {
        movepos = target->GetActorLocation();
    }
    AActor* self = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Self"));

    if (!!self)
    {
        UCEnemyStateComponent *statecomp = CHelpers::GetComponent<UCEnemyStateComponent>(self);
        FVector current = self->GetActorLocation();

        float distance = sqrt(pow(movepos.X - current.X, 2) + pow(movepos.Y - current.Y, 2));
        if (distance <= mNearDistance)
        {
            statecomp->Remove(ECurrentState::MOVE);
            statecomp->SetMode(EStateEnemyType::Idle, ECurrentState::NONESTATE);
            return EBTNodeResult::Succeeded;
        }
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}