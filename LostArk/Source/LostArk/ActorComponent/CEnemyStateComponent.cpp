#include "CEnemyStateComponent.h"
#include "../Global.h"
#include "cmath"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "GameFramework/Character.h"


#include "Animation/AnimMontage.h"

UCEnemyStateComponent::UCEnemyStateComponent()
{

}

void UCEnemyStateComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if ( 0 < mCurrentCooltime  )
        mCurrentCooltime -= DeltaTime;
  
}

void UCEnemyStateComponent::OperationSelect(const AActor* target)
{
    CheckNull(target);

    FVector ownerPos = GetOwner()->GetActorLocation();
    FVector targetPos = target->GetActorLocation();
    float x_ = (ownerPos.X - targetPos.X);
    float y_ = (ownerPos.Y - targetPos.Y);
    float distance = sqrt(x_ * x_ + y_ * y_);

    if (distance <= mAttackRange)
        SetActionMode();
    
    else
        SetApproachMode();
    
}

void UCEnemyStateComponent::SetIdleMode()
{
    mState = EStateEnemyType::Idle;
    SetMode(BYTE(EStateEnemyType::Idle));
}

void UCEnemyStateComponent::SetApproachMode()
{
    CheckFalse(IsIdleMode());
    mState = EStateEnemyType::Approach;

    SetMode(BYTE(EStateEnemyType::Approach));

}

void UCEnemyStateComponent::SetStrafeMode()
{
    CheckFalse(IsIdleMode());

    mState = EStateEnemyType::Strafe;
    SetMode(BYTE(EStateEnemyType::Strafe));

}

void UCEnemyStateComponent::SetActionMode()
{
    // 공격 쿨타임이 남아있다면
    if (0 < mCurrentCooltime)
        SetStrafeMode();

    else if ( mCurrentCooltime <= 0)
    {
        CLog::Print("Attack");

        mState = EStateEnemyType::Action;
        SetMode(BYTE(EStateEnemyType::Action));
        ACharacter *owner = Cast<ACharacter>(GetOwner());
        owner->PlayAnimMontage(AttackMontage);
        mCurrentCooltime = mCooltime;
    }
}

void UCEnemyStateComponent::SetDeathMode()
{
    mState = EStateEnemyType::Death;

    SetMode(BYTE(EStateEnemyType::Death));
}

void UCEnemyStateComponent::SetMode(BYTE num)
{
    ACharacter *owner = Cast<ACharacter>(GetOwner());
    AAIController *controller = Cast<AAIController>(owner->GetController());
    CheckNull(controller);

    controller->GetBlackboardComponent()->SetValueAsEnum("State", num);
}
