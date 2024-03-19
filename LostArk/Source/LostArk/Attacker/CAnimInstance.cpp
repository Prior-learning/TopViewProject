#include "CAnimInstance.h"
#include "../ActorComponent/CStateComponent.h"
#include "../Global.h"

void UCAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();
    mOwnerPawn = TryGetPawnOwner();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    CheckNull(mOwnerPawn);
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    Speed = mOwnerPawn->GetVelocity().Size2D();
    Direction = CalculateDirection(mOwnerPawn->GetVelocity(), mOwnerPawn->GetActorRotation());
    
    UCStateComponent *state = CHelpers::GetComponent<UCStateComponent>(mOwnerPawn);
    CheckNull(state); 

    AnimWeaponType = state->GetWeaponType();
    bAiming = state->IsAimMode();
    bDeath = state->IsDeathMode();
}
