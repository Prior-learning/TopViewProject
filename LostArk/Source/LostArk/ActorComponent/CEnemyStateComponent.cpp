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
    Add(EStateEnemyType::Idle, E_WHY_BLOCKED::NONE);
    Add(EStateEnemyType::Approach, E_WHY_BLOCKED::NONE);
    Add(EStateEnemyType::Strafe, E_WHY_BLOCKED::NONE);
    Add(EStateEnemyType::Action, E_WHY_BLOCKED::NONE);
    Add(EStateEnemyType::Death, E_WHY_BLOCKED::NONE);

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

void UCEnemyStateComponent::Remove( const E_WHY_BLOCKED &reason)
{
    mP_State[EStateEnemyType::Idle] &= ~reason;
    mP_State[EStateEnemyType::Approach] &= ~reason;
    mP_State[EStateEnemyType::Strafe] &= ~reason;
    mP_State[EStateEnemyType::Action] &= ~reason;
    mP_State[EStateEnemyType::Death] &= ~reason;
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
    
    CheckTrue(FlagCheck(EStateEnemyType::Idle, E_WHY_BLOCKED::DEATEH));

    Remove(E_WHY_BLOCKED::ATTACKING);
    Remove(E_WHY_BLOCKED::MOVE);
    Remove(E_WHY_BLOCKED::HITTED);

    SetMode(EStateEnemyType::Idle,E_WHY_BLOCKED::NONE);
}

void UCEnemyStateComponent::SetApproachMode()
{
    CheckTrue(FlagCheck(EStateEnemyType::Approach, E_WHY_BLOCKED::DEATEH));
    CheckTrue(FlagCheck(EStateEnemyType::Approach, E_WHY_BLOCKED::MOVE));
    CheckTrue(FlagCheck(EStateEnemyType::Approach, E_WHY_BLOCKED::ATTACKING));

    int ran = rand() % 2;
    switch (ran)
    {
    case 0:
        CLog::Log("Approach");
        SetMode(EStateEnemyType::Approach, E_WHY_BLOCKED::MOVE);
        return;
    case 1:
        CLog::Log("Strafe");
        SetMode(EStateEnemyType::Strafe, E_WHY_BLOCKED::MOVE);
        return;
    }
}

void UCEnemyStateComponent::SetStrafeMode()
{

    CheckTrue(FlagCheck(EStateEnemyType::Strafe, E_WHY_BLOCKED::DEATEH));
    CheckTrue(FlagCheck(EStateEnemyType::Strafe, E_WHY_BLOCKED::MOVE));
    CheckTrue(FlagCheck(EStateEnemyType::Strafe, E_WHY_BLOCKED::ATTACKING));

    SetMode(EStateEnemyType::Strafe,E_WHY_BLOCKED::MOVE);

}

void UCEnemyStateComponent::SetActionMode()
{
    CheckTrue(FlagCheck(EStateEnemyType::Action, E_WHY_BLOCKED::DEATEH));
    CheckTrue(FlagCheck(EStateEnemyType::Action, E_WHY_BLOCKED::ATTACKING));
    CheckTrue(FlagCheck(EStateEnemyType::Action, E_WHY_BLOCKED::MOVE));

  

    if ( mCurrentCooltime <= 0)
    {
        controller->ClearFocus(EAIFocusPriority::Default);// 수정하기
        SetMode(EStateEnemyType::Action, E_WHY_BLOCKED::ATTACKING);
        
        IICombat *combat = Cast<IICombat>(GetOwner());
        combat->Attack();

        mCurrentCooltime = mCooltime ;
    }
}

void UCEnemyStateComponent::SetDeathMode()
{
    controller->ClearFocus(EAIFocusPriority::Default);

    SetMode(EStateEnemyType::Death, E_WHY_BLOCKED::DEATEH);
}

void UCEnemyStateComponent::SetMode(const EStateEnemyType &type, const E_WHY_BLOCKED& reason)
{
    CheckNull(controller);
    mState = type;
    controller->GetBlackboardComponent()->SetValueAsEnum("State", BYTE(type));

    Add(EStateEnemyType::Idle, reason);
    Add(EStateEnemyType::Approach, reason);
    Add(EStateEnemyType::Strafe, reason);
    Add(EStateEnemyType::Action, reason);
    Add(EStateEnemyType::Death, reason);
}

bool UCEnemyStateComponent::FlagCheck(const EStateEnemyType &action, const E_WHY_BLOCKED &reason)
{     
    return reason == (mP_State[action] & reason);
}
