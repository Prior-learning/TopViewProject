#include "CENotifyMoveTo.h"
#include "AIController.h"
#include "GameFramework/Character.h"

#include "../Utilities/Defines.h"

FString UCENotifyMoveTo::GetNotifyName() const
{
    return "MoveToDirection";
}
void UCENotifyMoveTo::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (MeshComp == nullptr)
        return;
    if (MeshComp->GetOwner() == nullptr)
        return;

    ACharacter *owner = Cast<ACharacter>(MeshComp->GetOwner());
    CheckNull(owner);

    FVector current = owner->GetActorLocation();
    FVector direction;
    switch (mDirection)
    {
    case EDirection::Forward:
        direction = owner->GetActorForwardVector().GetSafeNormal();
        break;
    case EDirection::Back:
        direction = -owner->GetActorForwardVector().GetSafeNormal();
        break;
    case EDirection::Right:
        direction = owner->GetActorRightVector().GetSafeNormal();
        break;
    case EDirection::Left:
        direction = -owner->GetActorRightVector().GetSafeNormal();
        break;

    default:
        direction = {0, 0, 0};
        break;
    }

    

    
    AAIController *mController = Cast<AAIController>( owner->GetController());

    CheckNull(mController);

    mController->MoveTo(current + direction * mDistance);
    
}
