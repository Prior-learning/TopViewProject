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
	//p_State에 Key값인 action이 없다면 추가. 추가된 행동은 reason에 해당하는 이유로 실행할 수 없는 상태가 되는 것.
	P_State[action] |= reason;
}

void UCPlayerStateComponent::Remove(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		return;
	//Add함수로 추가된 action을 제거.
	P_State[action] &= ~reason;
}


const bool UCPlayerStateComponent::IsContains(const E_State& action)
{
	if (P_State.Contains(action) == false)
		return false;


	// 해당 상태에 해당하는 비트 플래그 중 하나라도 활성화되어 있는지 확인. false라면 해당 행동이 가능. 아니라면 행동이 불가능하도록.
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
