#include "CBTService_ChangeSpeed.h"
#include "AIController.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTService_ChangeSpeed::UCBTService_ChangeSpeed() {}

void UCBTService_ChangeSpeed::TickNode(UBehaviorTreeComponent &OwnerComp,
                                      uint8 *NodeMemory, float DeltaSeconds) {
  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

  ACharacter *owner = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());

  if (owner == nullptr)
    return;
  owner->GetCharacterMovement()->MaxWalkSpeed = mSpeed;
}