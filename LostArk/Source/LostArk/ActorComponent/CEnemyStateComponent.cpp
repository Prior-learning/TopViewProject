#include "CEnemyStateComponent.h"
#include "../Global.h"
#include "cmath"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "GameFramework/Character.h"


#include "Animation/AnimMontage.h"
#include "../Combat/ICombat.h"

UCEnemyStateComponent::UCEnemyStateComponent()
{
    
}

void UCEnemyStateComponent::BeginPlay()
{
    Super::BeginPlay();
    mHp = MaxHp;

    ACharacter *owner = Cast<ACharacter>(GetOwner());
    controller = Cast<AAIController>(owner->GetController());
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

void UCEnemyStateComponent::Add(const EStateEnemyType &action, const E_WHY_BLOCKED &reason)
{
    if (!mP_State.Contains(action))
        mP_State.Emplace(action);
    mP_State[action] |= reason;
}

void UCEnemyStateComponent::Remove(const EStateEnemyType &action, const E_WHY_BLOCKED &reason)
{
    if (!mP_State.Contains(action))
        return;
    mP_State[action] &= ~reason;
}

const bool UCEnemyStateComponent::IsContains(const EStateEnemyType &action)
{
    if (!mP_State.Contains(action))
        return false;
    return true;
}

void UCEnemyStateComponent::Clear(const EStateEnemyType &action)
{
}



void UCEnemyStateComponent::Take_Damage(float DamageAmount)
{
    mHp -= DamageAmount;

    if (mHp <= 0)
        SetDeathMode();
}

void UCEnemyStateComponent::SetIdleMode()
{
    CheckFalse(IsContains(EStateEnemyType::Idle));

    mState = EStateEnemyType::Idle;
    SetMode(BYTE(EStateEnemyType::Idle));
}

void UCEnemyStateComponent::SetApproachMode()
{
    CheckTrue(IsDeathMode());
    CheckFalse(IsIdleMode());
    mState = EStateEnemyType::Approach;

    SetMode(BYTE(EStateEnemyType::Approach));

}

void UCEnemyStateComponent::SetStrafeMode()
{
    CheckTrue(IsDeathMode());
    CheckFalse(IsIdleMode());

    mState = EStateEnemyType::Strafe;
    SetMode(BYTE(EStateEnemyType::Strafe));

}

void UCEnemyStateComponent::SetActionMode()
{
    CheckTrue(IsDeathMode());
    CheckTrue(IsActionMode());
  
    // 공격 쿨타임이 남아있다면
    if (0 < mCurrentCooltime)
        SetStrafeMode();

    else if ( mCurrentCooltime <= 0)
    {
        controller->ClearFocus(EAIFocusPriority::Default);// 수정하기

        mState = EStateEnemyType::Action;
        SetMode(BYTE(EStateEnemyType::Action));
        
        IICombat *combat = Cast<IICombat>(GetOwner());
       
        combat->Attack();

        mCurrentCooltime = mCooltime ;
    }
}

void UCEnemyStateComponent::SetDeathMode()
{
    mState = EStateEnemyType::Death;

    controller->ClearFocus(EAIFocusPriority::Default);
    SetMode(BYTE(EStateEnemyType::Death));
}

void UCEnemyStateComponent::SetMode(BYTE num)
{
    CheckNull(controller);
    controller->GetBlackboardComponent()->SetValueAsEnum("State", num);
}
