#include "CPlayerStateComponent.h"


UCPlayerStateComponent::UCPlayerStateComponent() 
: bFiring(false), bAiming(false), bCanMove(true)
{
   
}

void UCPlayerStateComponent::Initialize()
{

}

void UCPlayerStateComponent::Destroy()
{
    P_State.Empty();
}

void UCPlayerStateComponent::Add(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		P_State.Emplace(action);
	//p_State�� Key���� action�� ���ٸ� �߰�. �߰��� �ൿ�� reason�� �ش��ϴ� ������ ������ �� ���� ���°� �Ǵ� ��.
	P_State[action] |= reason;
}

void UCPlayerStateComponent::Remove(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		return;
	//Add�Լ��� �߰��� action�� ����.
	P_State[action] &= ~reason;
}


const bool UCPlayerStateComponent::IsContains(const E_State& action)
{
	if (P_State.Contains(action) == false)
		return false;


	// �ش� ���¿� �ش��ϴ� ��Ʈ �÷��� �� �ϳ��� Ȱ��ȭ�Ǿ� �ִ��� Ȯ��. false��� �ش� �ൿ�� ����. �ƴ϶�� �ൿ�� �Ұ����ϵ���.
	uint64 StateFlag = P_State[action];
	return StateFlag != 0;
}

void UCPlayerStateComponent::Clear(const E_State& action)
{
	P_State.Remove(action);
}

void UCPlayerStateComponent::SetRoll()
{
    Add(E_State::Aim, E_WHY_BLOCKED::ROLLING);
    Add(E_State::Attack, E_WHY_BLOCKED::ROLLING);
    Add(E_State::Reload, E_WHY_BLOCKED::ROLLING);
    Add(E_State::Roll, E_WHY_BLOCKED::ROLLING);
}

void UCPlayerStateComponent::UnSetRoll()
{
    Remove(E_State::Aim, E_WHY_BLOCKED::ROLLING);
    Remove(E_State::Attack, E_WHY_BLOCKED::ROLLING);
    Remove(E_State::Reload, E_WHY_BLOCKED::ROLLING);
    Remove(E_State::Roll, E_WHY_BLOCKED::ROLLING);
}

void UCPlayerStateComponent::SetAim()
{
    bAiming = true;
    Add(E_State::Reload, E_WHY_BLOCKED::AIMING);
}

void UCPlayerStateComponent::UnSetAim()
{
    bAiming = false;
    Remove(E_State::Reload, E_WHY_BLOCKED::AIMING);
}

void UCPlayerStateComponent::SetFire()
{
    bFiring = true;
    Add(E_State::Reload, E_WHY_BLOCKED::ATTACKING);
}

void UCPlayerStateComponent::UnSetFire()
{
    bFiring = false;
    Remove(E_State::Reload, E_WHY_BLOCKED::ATTACKING);
}

void UCPlayerStateComponent::SetAirborn()
{
    bCanMove = false;
    Add(E_State::Aim, E_WHY_BLOCKED::AirBorned);
    Add(E_State::Attack, E_WHY_BLOCKED::AirBorned);
    Add(E_State::Reload, E_WHY_BLOCKED::AirBorned);
    Add(E_State::Roll, E_WHY_BLOCKED::AirBorned);
}

void UCPlayerStateComponent::UnSetAirborn()
{
    bCanMove = true;
    Remove(E_State::Aim, E_WHY_BLOCKED::AirBorned);
    Remove(E_State::Attack, E_WHY_BLOCKED::AirBorned);
    Remove(E_State::Reload, E_WHY_BLOCKED::AirBorned);
    Remove(E_State::Roll, E_WHY_BLOCKED::AirBorned);
}

void UCPlayerStateComponent::SetReload()
{
}

void UCPlayerStateComponent::UnSetReload()
{
}

void UCPlayerStateComponent::SetSkill()
{
    bCanMove = false;
    Add(E_State::Aim, E_WHY_BLOCKED::SKILLUSE);
    Add(E_State::Reload, E_WHY_BLOCKED::SKILLUSE);
    Add(E_State::Roll, E_WHY_BLOCKED::SKILLUSE);
}

void UCPlayerStateComponent::UnSetSkill()
{
    bCanMove = true;
    Remove(E_State::Aim, E_WHY_BLOCKED::SKILLUSE);
    Remove(E_State::Reload, E_WHY_BLOCKED::SKILLUSE);
    Remove(E_State::Roll, E_WHY_BLOCKED::SKILLUSE);
}

void UCPlayerStateComponent::SetSniping()
{
    bCanMove = false;
    bAiming = true;
    Add(E_State::Aim, E_WHY_BLOCKED::SKILLUSE);
    Add(E_State::Reload, E_WHY_BLOCKED::SKILLUSE);
    Add(E_State::Roll, E_WHY_BLOCKED::SKILLUSE);
}

void UCPlayerStateComponent::UnSetSniping()
{
    bCanMove = true;
    bAiming = false;
    Remove(E_State::Aim, E_WHY_BLOCKED::SKILLUSE);
    Remove(E_State::Reload, E_WHY_BLOCKED::SKILLUSE);
    Remove(E_State::Roll, E_WHY_BLOCKED::SKILLUSE);
}
