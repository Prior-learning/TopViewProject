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

