#include "CEnemyStateComponent.h"
#include "../Global.h"
#include "cmath"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "GameFramework/Character.h"


#include "Animation/AnimMontage.h"
#include "../Combat/ICombat.h"
#include "../Widget/CEnemyHpWidget.h"

UCEnemyStateComponent::UCEnemyStateComponent()
{
    
}

void UCEnemyStateComponent::BeginPlay()
{
    Super::BeginPlay();

    mHp = MaxHp;

    ACharacter *owner = Cast<ACharacter>(GetOwner());
    mController = Cast<AAIController>(owner->GetController());

    SetMode(EStateEnemyType::Idle, ECurrentState::NONESTATE);
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

void UCEnemyStateComponent::Add(const ECurrentState &reason)
{
    mFlagState |= reason;
}

void UCEnemyStateComponent::Remove( const ECurrentState &reason)
{
    mFlagState &= ~reason;
}

void UCEnemyStateComponent::Take_Damage(float& DamageAmount)
{
    mHp -= DamageAmount;
    UCEnemyHpWidget::GetInstance()->UpdateProgressBar(mHp/MaxHp);
    if (mHp <= 0)
        SetDeathMode();

}

void UCEnemyStateComponent::SetIdleMode() 
{
    
    CheckTrue(FlagCheck(ECurrentState::DEATEH));

    Remove(ECurrentState::ATTACKINGSTATE);
    Remove(ECurrentState::MOVE);
    Remove(ECurrentState::HITTED);

    SetMode(EStateEnemyType::Idle,ECurrentState::NONESTATE);
}

void UCEnemyStateComponent::SetApproachMode() 
{
    CheckTrue(FlagCheck(ECurrentState::DEATEH));
    CheckTrue(FlagCheck(ECurrentState::MOVE));
    CheckTrue(FlagCheck(ECurrentState::ATTACKINGSTATE));

    if (bStraff)
    {
        int ran = rand() % 2;
        switch (ran)
        {
        case 0:
            CLog::Log("Approach");
            SetMode(EStateEnemyType::Approach, ECurrentState::MOVE);
            return;
        case 1:
            CLog::Log("Strafe");
            SetMode(EStateEnemyType::Strafe, ECurrentState::MOVE);
            mController->SetFocus(Cast<AActor>(mController->GetBlackboardComponent()->GetValueAsObject("Target")));
            return;
        }
    }
    else
    {
        int ran = rand() % 2;
        switch (ran)
        {
        case 0:
            SetMode(EStateEnemyType::Approach, ECurrentState::MOVE);
            break;
        case 1:

            SetMode(EStateEnemyType::Dash, ECurrentState::ATTACKINGSTATE);
            IICombat *combat = Cast<IICombat>(GetOwner());
            combat->Attack();
            break;
        }
        return;
    }
}



void UCEnemyStateComponent::SetActionMode() 
{

    CheckTrue(FlagCheck(ECurrentState::DEATEH));
    CheckTrue(FlagCheck(ECurrentState::ATTACKINGSTATE));
    CheckTrue(FlagCheck(ECurrentState::MOVE));

    if ( mCurrentCooltime <= 0)
    {
        bool bChk = mHp / MaxHp <= 0.9f; // 반피 이하면 true
        if (mMaxPhase && bChk)
        {
            mMaxPhase--;
            SetMode(EStateEnemyType::Skill, ECurrentState::ATTACKINGSTATE);
        }
        else
            SetMode(EStateEnemyType::Action, ECurrentState::ATTACKINGSTATE);
        
        IICombat *combat = Cast<IICombat>(GetOwner());
        combat->Attack();

        mCurrentCooltime = mCooltime ;
    }
}

void UCEnemyStateComponent::SetDeathMode() 
{
    SetMode(EStateEnemyType::Death, ECurrentState::DEATEH);
}

void UCEnemyStateComponent::SetMode(const EStateEnemyType &type, const ECurrentState& reason)
{
    CheckNull(mController);
    mState = type;
    mController->GetBlackboardComponent()->SetValueAsEnum("State", BYTE(type));
    Add(reason);
}

bool UCEnemyStateComponent::FlagCheck(const ECurrentState &reason) const
{
    return reason == (mFlagState & reason);
}

