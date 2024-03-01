#include "CPlayerStateComponent.h"


UCPlayerStateComponent::UCPlayerStateComponent() 
{

}

void UCPlayerStateComponent::Initialize()
{

}

void UCPlayerStateComponent::Destroy()
{
}

void UCPlayerStateComponent::Add(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		P_State.Emplace(action);

	P_State[action] |= reason;
}

void UCPlayerStateComponent::Remove(const E_State& action, const E_WHY_BLOCKED& reason)
{
	if (P_State.Contains(action) == false)
		return;

	P_State[action] &= ~reason;
}


const bool UCPlayerStateComponent::IsContains(const E_State& action)
{
	if (P_State.Contains(action) == false)
		return false;


	// 해당 상태에 해당하는 비트 플래그 중 하나라도 활성화되어 있는지 확인
	uint64 StateFlag = P_State[action];
	return StateFlag != 0;
}

void UCPlayerStateComponent::Clear(const E_State& action)
{
	P_State.Remove(action);
}

