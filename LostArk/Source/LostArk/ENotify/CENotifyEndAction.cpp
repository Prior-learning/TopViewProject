#include "CENotifyEndAction.h"
#include "../Global.h"
#include "../ActorComponent/CEnemyStateComponent.h"

FString UCENotifyEndAction::GetNotifyName() const
{
    return "EndAction";
}


void UCENotifyEndAction::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    CheckNull(MeshComp);
    UCEnemyStateComponent *State = CHelpers::GetComponent<UCEnemyStateComponent>(MeshComp->GetOwner());
    if (State == nullptr)
    {
        CLog::Log("StateComponent is nullptr");
        return;
    }
    State->SetIdleMode();
}