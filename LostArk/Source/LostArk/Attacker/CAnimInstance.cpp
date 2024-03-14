#include "CAnimInstance.h"
#include "../ActorComponent/CStateComponent.h"
#include "../Global.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    CheckNull(OwnerCharacter);
    Super::NativeUpdateAnimation(DeltaSeconds);

    Speed = OwnerCharacter->GetVelocity().Size2D();
    Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
    UCStateComponent *state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
    CheckNull(state); 

    AnimWeaponType = state->GetWeaponType();
    bAiming = state->IsAimMode();
    bDeath = state->IsDeathMode();
}
