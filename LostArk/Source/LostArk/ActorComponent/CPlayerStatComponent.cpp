#include "CPlayerStatComponent.h"

UCPlayerStatComponent::UCPlayerStatComponent() : mStatus({100.f,100.f,100.f, 100.f, false})
{
}

void UCPlayerStatComponent::AddHP(float add)
{
    if (mStatus.HealthPoint + add >= mStatus.MaxHealth)
        mStatus.HealthPoint = mStatus.MaxHealth;
    else
        mStatus.HealthPoint += add;

     if (OnHealthChanged.IsBound())
        OnHealthChanged.Broadcast();
}

void UCPlayerStatComponent::MinusHP(float minus)
{
    if (mStatus.HealthPoint - minus <= 0.f)
    {
        mStatus.HealthPoint = 0.f;
        mStatus.bDead = true;
    }
    else
        mStatus.HealthPoint -= minus;

    if (OnHealthChanged.IsBound())
        OnHealthChanged.Broadcast();
}

void UCPlayerStatComponent::AddMP(float add)
{
    if (mStatus.ManaPoint + add >= mStatus.MaxMana)
        mStatus.ManaPoint = mStatus.MaxMana;
    else
        mStatus.ManaPoint += add;

    if (OnManaChanged.IsBound())
        OnManaChanged.Broadcast();
}

bool UCPlayerStatComponent::MinusMP(float minus)
{
    if (mStatus.ManaPoint - minus <= 0.f)
    {
        mStatus.ManaPoint = 0.f;
        return false;

    }
    else
    {
        mStatus.ManaPoint -= minus;
         if (OnManaChanged.IsBound())
            OnManaChanged.Broadcast();

        return true;
    }
}
