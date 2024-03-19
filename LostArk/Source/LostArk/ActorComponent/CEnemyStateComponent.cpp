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
    mController = Cast<AAIController>(owner->GetController());

    SetMode(EStateEnemyType::Idle, E_WHY_BLOCKED::NONE);
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

void UCEnemyStateComponent::Add(const E_WHY_BLOCKED &reason)
{
    mFlagState |= reason;
}

void UCEnemyStateComponent::Remove( const E_WHY_BLOCKED &reason)
{
    mFlagState &= ~reason;
}

void UCEnemyStateComponent::Take_Damage(float& DamageAmount)
{
    mHp -= DamageAmount;
    
    if (mHp <= 0)
        SetDeathMode();

}

void UCEnemyStateComponent::SetIdleMode() 
{
    
    CheckTrue(FlagCheck(E_WHY_BLOCKED::DEATEH));

    Remove(E_WHY_BLOCKED::ATTACKING);
    Remove(E_WHY_BLOCKED::MOVE);
    Remove(E_WHY_BLOCKED::HITTED);

    SetMode(EStateEnemyType::Idle,E_WHY_BLOCKED::NONE);
}

void UCEnemyStateComponent::SetApproachMode() 
{
    CheckTrue(FlagCheck(E_WHY_BLOCKED::DEATEH));
    CheckTrue(FlagCheck(E_WHY_BLOCKED::MOVE));
    CheckTrue(FlagCheck(E_WHY_BLOCKED::ATTACKING));

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
        mController->SetFocus(Cast<AActor>(mController->GetBlackboardComponent()->GetValueAsObject("Target")));
        return;
    }
}



void UCEnemyStateComponent::SetActionMode() 
{

    CheckTrue(FlagCheck(E_WHY_BLOCKED::DEATEH));
    CheckTrue(FlagCheck(E_WHY_BLOCKED::ATTACKING));
    CheckTrue(FlagCheck(E_WHY_BLOCKED::MOVE));

  

    if ( mCurrentCooltime <= 0)
    {
       
        SetMode(EStateEnemyType::Action, E_WHY_BLOCKED::ATTACKING);
        
        IICombat *combat = Cast<IICombat>(GetOwner());
        combat->Attack();

        mCurrentCooltime = mCooltime ;
    }
}

void UCEnemyStateComponent::SetDeathMode() 
{
    SetMode(EStateEnemyType::Death, E_WHY_BLOCKED::DEATEH);
}

void UCEnemyStateComponent::SetMode(const EStateEnemyType &type, const E_WHY_BLOCKED& reason)
{
    CheckNull(mController);
    mState = type;
    mController->GetBlackboardComponent()->SetValueAsEnum("State", BYTE(type));
    Add(reason);
}

bool UCEnemyStateComponent::FlagCheck(const E_WHY_BLOCKED &reason) const
{
    return reason == (mFlagState & reason);
}

