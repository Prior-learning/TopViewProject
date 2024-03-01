#include "CEnemyStateComponent.h"
#include "../Global.h"
#include "cmath"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "GameFramework/Character.h"

UCEnemyStateComponent::UCEnemyStateComponent()
{
}

void UCEnemyStateComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    mCurrentCooltime -= DeltaTime;
    CLog::Print(mCurrentCooltime);
}

void UCEnemyStateComponent::OperationSelect(const AActor* target)
{
    
    FVector ownerPos = GetOwner()->GetActorLocation();
    FVector targetPos = target->GetActorLocation();
    float x_ = (ownerPos.X - targetPos.X);
    float y_ = (ownerPos.Y - targetPos.Y);
    float distance = sqrt(x_ * x_ + y_ * y_);

    //CLog::Print(distance);
    if (distance <= mAttackRange)
    {
        SetActionMode();
    }
    else
    {
        SetApproachMode();
    }
    
}

void UCEnemyStateComponent::SetIdleMode()
{
    mState = EStateEnemyType::Idle;

    ACharacter *owner = Cast<ACharacter>(GetOwner());
    AAIController *controller = Cast<AAIController>(owner->GetController());
    CheckNull(controller);

    controller->GetBlackboardComponent()->SetValueAsEnum("State", 0);
}

void UCEnemyStateComponent::SetApproachMode()
{
    mState = EStateEnemyType::Approach;

    ACharacter *owner = Cast<ACharacter>(GetOwner());
    AAIController *controller = Cast<AAIController>(owner->GetController());
    CheckNull(controller);

    controller->GetBlackboardComponent()->SetValueAsEnum("State", 1);
}

void UCEnemyStateComponent::SetStrafeMode()
{
    mState = EStateEnemyType::Strafe;

    ACharacter *owner = Cast<ACharacter>(GetOwner());
    AAIController *controller = Cast<AAIController>(owner->GetController());
    CheckNull(controller);

    controller->GetBlackboardComponent()->SetValueAsEnum("State", 2);
}

void UCEnemyStateComponent::SetActionMode()
{
    // 공격 쿨타임이 남아있다면
    if (0 < mCurrentCooltime && mState == EStateEnemyType::Idle) 
    {
        
        SetStrafeMode();
    }
    else if ( mCurrentCooltime <= 0)
    {
        CLog::Print("Attack");
        mState = EStateEnemyType::Action;

        ACharacter *owner = Cast<ACharacter>(GetOwner());
        AAIController *controller = Cast<AAIController>(owner->GetController());
        CheckNull(controller);

        controller->GetBlackboardComponent()->SetValueAsEnum("State", 3);
        mCurrentCooltime = mCooltime;
    }
}

void UCEnemyStateComponent::SetDeathMode()
{
    mState = EStateEnemyType::Death;

    ACharacter *owner = Cast<ACharacter>(GetOwner());
    AAIController *controller = Cast<AAIController>(owner->GetController());
    CheckNull(controller);

    controller->GetBlackboardComponent()->SetValueAsEnum("State", 4);
}
