#include "CPlayerActionComponent.h"
#include "../Global.h"

//#include "CPlayerStateComponent.h"
#include "GameFramework/Character.h"


UCPlayerActionComponent::UCPlayerActionComponent()
{
   
}

void UCPlayerActionComponent::BeginPlay()
{
    Super::BeginPlay();

    ACharacter *character = Cast<ACharacter>(GetOwner());
    mState = CHelpers::GetComponent<UCPlayerStateComponent>(character);
  
}

void UCPlayerActionComponent::SetUnarmed()
{
    CheckNull(mState);
    if (mState->GetWeaponType() != E_WeaponType::UnArmed)
        mState->SetUnarmed();
}


void UCPlayerActionComponent::SetPrimary()
{
    CheckNull(mState);

    if (mState->GetWeaponType() == E_WeaponType::UnArmed)
        mState->SetPrimary();
}

void UCPlayerActionComponent::SetAim()
{
    CheckNull(mState);

    if (!mState->IsContains(E_State::Aim) && !mState->IsAimMode() && mState->GetWeaponType() != E_WeaponType::UnArmed)
    mState->SetAiming();
}

void UCPlayerActionComponent::UnSetAim()
{
    CheckNull(mState);

    if (mState->IsAimMode())
    mState->UnSetAiming();
}

void UCPlayerActionComponent::DoAttack()
{
}

void UCPlayerActionComponent::DoRoll()
{
    CheckNull(mState);

    CheckTrue(mState->IsContains(E_State::Roll));
    mState->Add(E_State::Aim, E_WHY_BLOCKED::ROLLING);
    mState->Add(E_State::Attack, E_WHY_BLOCKED::ROLLING);
    mState->Add(E_State::Reload, E_WHY_BLOCKED::ROLLING);
    mState->Add(E_State::Roll, E_WHY_BLOCKED::ROLLING);
}

void UCPlayerActionComponent::EndRoll()
{
    CheckNull(mState);

    mState->Remove(E_State::Aim, E_WHY_BLOCKED::ROLLING);
    mState->Remove(E_State::Attack, E_WHY_BLOCKED::ROLLING);
    mState->Remove(E_State::Reload, E_WHY_BLOCKED::ROLLING);
    mState->Remove(E_State::Roll, E_WHY_BLOCKED::ROLLING);
}


